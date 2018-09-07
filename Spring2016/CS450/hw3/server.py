#!/usr/bin/env python

import select
import socket
import sys
import random

clients = 0

def whoWon(firstCard, secondCard):
    winners = []
    if (firstCard % 14) > (secondCard % 14):
        winners.append(1)
        winners.append(0)
        return winners

    elif (firstCard % 14) < (secondCard % 14):
        winners.append(0)
        winners.append(1)
        return winners

    elif (firstCard % 14) == (secondCard % 14):
        winners.append(0)
        winners.append(0)
        return winners

#end whoWon


def splitTheDeck():
    cards = range(52)
    random.shuffle(cards)
    cardsBottom = cards[0:26]
    cardsTop = cards[26:52]
    gameStartString = []
    startString = '\x01'
    for i in cardsBottom:
        startString += chr(i)

    gameStartString.append(startString)
    startString = '\x01'
    for i in cardsTop:
        startString += chr(i)

    gameStartString.append(startString)
    return gameStartString
#end splitTheDeck()

def findClients(accepted):
    for first in accepted:
        if first[2] == -1:
            for second in accepted:
                if second[2] == -1 and first[0] != second[0]:
                    deck = splitTheDeck()
                    first[2] = accepted.index(second)
                    first[3] = deck[0]
                    second[2] = accepted.index(first)
                    second[3] = deck[1]

    return accepted
#end findClients

def killall(i, j):
    i[0].sendall("SERVER FORCED CLOSE")
    j[0].sendall("SERVER FORCED CLOSE")
    i[0].close()
    j[0].close()
    clients -= 2
#end killall

def serve(port):
    global clients
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind(('',port))
    server.listen(5)
    print 'Listening to port',port,'...'
    inputs = [server,sys.stdin]
    running = 1
    accepted = [];
    while running:
        try:
            inputready,outputready,exceptready = select.select(inputs, [], [])
        except select.error, e:
            break
        except socket.error, e:
            break

        for s in inputready:
            if s == server:
                # handle the server socket
                client,address = server.accept()
                inputs.append(client)
                accepted.append(list((client,address, -1, '', 0, 0, 0)))
                clients += 1
                print clients
                if clients % 2 == 0:
                    print 'We have a couple'
                    accepted = findClients(accepted)

            elif s == sys.stdin:
                # handle standard input
                junk = sys.stdin.readline()

            else:
                # handle all other sockets
                try:
                    data = s.recv(2)
                    if data:
                        for i in accepted:
                            if i[0] is s:
                                if i[2] == -1:
                                    j = list((client,address,-1, '',0,0,0))
                                else:
                                    j = accepted[i[2]]
                                if i[4] == 0 and i[5] == 0:
                                    if ord(data[0]) == 0:
                                        i[4] = 1
                                        i[5] = 1
                                        if j[4] == 1:
                                            i[0].sendall(i[3])
                                            j[0].sendall(j[3])
                                            j[5] = 0
                                            i[5] = 0

                                    else:
                                        inputs.remove(s)
                                        accepted.remove(i)
                                        accepted.remove(j)

                                elif i[4] == 1 and i[5] == 0:
                                    if ord(data[0]) == 2:
                                        i[4] = 2
                                        i[5] = 1
                                        i[3] = data
                                        i[6] += 1
                                        if j[4] == 2:
                                            compareResult = whoWon(ord(i[3][1]), ord(j[3][1]))
                                            if compareResult[0] > compareResult[1]:
                                                i[0].sendall('\x03\x00')
                                                j[0].sendall('\x03\x01')

                                            elif compareResult[0] < compareResult[1]:
                                                i[0].sendall('\x03\x01')
                                                j[0].sendall('\x03\x00')

                                            elif compareResult[0] == compareResult[1]:
                                                i[0].sendall('\x03\x02')
                                                j[0].sendall('\x03\x02')

                                            i[5] = 0
                                            j[5] = 0
                                            i[4] = 1
                                            j[4] = 1
                                            if i[6] == 26:
                                                clients -=2
                                                inputs.remove(i[0])
                                                inputs.remove(j[0])
                                                accepted.remove(i)
                                                accepted.remove(j)

                                    else:
                                        inputs.remove(i[0])
                                        inputs.remove(j[0])
                                        accepted.remove(i)
                                        accepted.remove(j)

                    else:
                        inputs.remove(s)
                        for i in accepted:
                            if i is s:
                                iputs.remove(accepted[i[2]][0])
                                accepted.remove(accepted[i[2]])
                                accepted.remove(i)

                except socket.error, e:
                    # Remove
                    inputs.remove(s)
                    for i in acccepted:
                        if i is s:
                            inputs.remove(accepted[i[2]][0])
                            accepted.remove(accepted[i[2]])
                            accepted.remove(i)

    server.close()
#end serv

serve(int(sys.argv[1]))
