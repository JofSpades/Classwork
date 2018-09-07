#!/usr/bin/python

import thread
import socket
import random
import sys
import time


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


def serveClient(client):
    global cardsBottom, cardsTop
    gameStart = False
    playCount = 0
    requestOne = ''
    requestTwo = ''
    gameStartString = []
    startString = '\x01'
    for i in cardsBottom:
        startString += chr(i)

    gameStartString.append(startString)
    startString = '\x01'
    for i in cardsTop:
        startString += chr(i)

    gameStartString.append(startString)

    while 1:
        requestOne = client[0][0].recv(2)
        requestTwo = client[1][0].recv(2)
        if not gameStart :
            if ord(requestOne[0]) == 0 and ord(requestTwo[0]) == 0:
                gameStart = True
                client[0][0].sendall(gameStartString[0])
                client[1][0].sendall(gameStartString[1])

        else:
            if playCount == 26:
                break
            elif ord(requestOne[0]) == 2 and ord(requestTwo[0]) == 2:
                playCount += 1
                compareResult = whoWon(ord(requestOne[1]), ord(requestTwo[1]))
                if compareResult[0] > compareResult[1]:
                    client[0][0].sendall('\x03\x00')
                    client[1][0].sendall('\x03\x01')

                elif compareResult[0] < compareResult[1]:
                    client[0][0].sendall('\x03\x01')
                    client[1][0].sendall('\x03\x00')

                elif compareResult[0] == compareResult[1]:
                    client[0][0].sendall('\x03\x02')
                    client[1][0].sendall('\x03\x02')

    client[1][0].close()
    client[0][0].close()
#end serveClient

def server(serverIP, gameSocket):
    global numberClients
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind((serverIP, gameSocket))
    sock.listen(5)
    connectionArray = []
    for i in range(numberClients):
        connectionArray.append(sock.accept())
        if len(connectionArray) != 2:
            pass
        else :
            break

    serveClient(connectionArray)
    sock.close()
#end server

def client(clientIP, gameSocket):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    score = 0
    sock.connect((clientIP, gameSocket))
    sock.sendall('\x00\x00')
    recieved = sock.recv(27)
    if ord(recieved[0]) == 1:
        print 'GAME STARTED'
        cardPile = []
        cardPile = recieved[1:]
        for i in range(len(cardPile)):
            print 'SENDING'
            #time.sleep(2)
            print ord(cardPile[i])
            sendString = '\x02' + cardPile[i]
            sock.sendall(sendString)
            print 'SENT'
            recieved = sock.recv(2)
            print ord(recieved[0])
            print ord(recieved[1])
            if ord(recieved[0]) == 3:
                if ord(recieved[1]) == 0:
                    score += 1
                    print score

                elif ord(recieved[1]) == 1:
                    score -= 1
                    print score

                elif ord(recieved[1]) == 2:
                    score -= 0
                    print score

            else:
                pass

        if score > 0:
            print 'YOU WON'

        elif score < 0:
            print 'YOU LOST'

        else:
            print 'IT WAS A TIE'

    sock.close()
#end client

#main
if len(sys.argv) == 4:
    if str(sys.argv[1]) == 'client':
        client(sys.argv[2],int(sys.argv[3]))
    elif str(sys.argv[1]) == 'server':
        cards = range(52)
        random.shuffle(cards)
        cardsBottom = cards[0:26]
        cardsTop = cards[26:52]
        numberClients = 2
        server(str(sys.argv[2]), int(sys.argv[3]))
else:
    print 'IMPROPER AMOUNT OF ARGUMENTS'

