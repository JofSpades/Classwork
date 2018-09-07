// 
// F# program to compute windshills
//
// Maxwel Petersen
// U. of Illinois, Chicago
// CS341, Fall 2015
// Homework 4
// 

#light

let windchill T W =
    let WC = 35.7 + (0.6 * T) - (35.7 * System.Math.Pow(W, 0.16)) + (0.43 * (T * System.Math.Pow(W, 0.16)))
    WC

[<EntryPoint>]
let main argv = 
    printfn "Please enter a temprature (degrees F): "
    let input = System.Console.ReadLine()
    let T = System.Convert.ToDouble(input)
    let WS = [1.0 .. 20.0]
    let windchills = List.map (fun W -> windchill T W ) WS
    printfn ""
    printfn "Windchills:"
    printfn "%A" windchills
    printfn ""
    0 // return an integer exit code
