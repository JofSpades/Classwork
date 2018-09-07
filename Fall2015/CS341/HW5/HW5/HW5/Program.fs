// 
// F# program to analyze rainfall data
// 
// Maxwell Petersen
// U. of Illinois, Chicago
// CS341, Fall 2015
// Homework 5
//

#light

//
// ReadFile: reads a file line by line, returning a list
// of strings, one per line.
//
let ReadFile filename =
    [ for line in System.IO.File.ReadLines(filename) -> line ]

//
// ParseLine: given a line from the rainfall file, parses this
// string into list of double values starting with the year, error
// rate, and then the 12 rainfall values (one per month).
//
let ParseLine (line:string) =
    let strings = line.Split('\t')
    let strlist = Array.toList(strings)
    let values = List.map (fun x -> System.Double.Parse(x, System.Globalization.NumberFormatInfo.InvariantInfo)) strlist
    values

//
// Recusisivly computes out the avrages of the list
//
let rec RainAverageByYear (values: double list list) =
    if values = [] then
        []
    else 
        printfn "%i: %A" (int ((values.Head).Head)) (List.average (values.Head).Tail.Tail)
        RainAverageByYear values.Tail

//
// Allows for the retrieval of a list of months
//
let rec GetMonth (values: double list list) month = 
    if values = [] then
       []
    else
        (List.nth (values.Head) (month + 1)) :: GetMonth values.Tail month


//
// Makes new lists of the data per month then prints it out
//
let rec RainAverageByMonth (values: double list list) (months: string list) count =
    if months = [] then
        []
    else
        printfn "%s: %A" months.Head (List.average (GetMonth values count))
        RainAverageByMonth values months.Tail (count + 1)

//
// Finds the Max of a list list
//
let rec ListListMax (values:double list list) maxSoFar =
    if values = [] then
        maxSoFar
    elif List.max values.Head > maxSoFar then
        ListListMax values.Tail (List.max values.Head)
    else
        ListListMax values.Tail maxSoFar

//
// Finds the Min of a list list
//
let rec ListListMin (values:double list list) minSoFar =
    if values = [] then
        minSoFar
    elif List.min values.Head < minSoFar then
        ListListMin values.Tail (List.min values.Head)
    else
        ListListMin values.Tail minSoFar
      
//
// Cleaning function
//
let rec Clean (values: double list list) = 
    if values = [] then
        []
    else
        (values.Head).Tail.Tail :: Clean values.Tail

//
// Finds the year of the rain value
//
let rec FindYear (values:double list list) rain count =
    if values = [] then
        -1
    elif List.exists (fun elem -> elem = rain) (values.Head).Tail.Tail then
        count
    else
        FindYear values.Tail rain (count + 1)

//
// Function to find the Max and Min
//
let MaxAndMin (values:double list list) =
    let cleaned = Clean values
    let max = ListListMax cleaned (cleaned.Head).Head
    let yearMaxList = (List.nth values (FindYear values max 0))
    let monthMax = (List.findIndex (fun elem -> elem = max) yearMaxList.Tail.Tail) + 1
    printfn "Max rainfall:  %A, %A/%A" max monthMax (int(yearMaxList.Head))
    let min = ListListMin cleaned (cleaned.Head).Head
    let yearMinList = (List.nth values (FindYear values min 0))
    let monthMin = (List.findIndex (fun elem -> elem = min) yearMinList.Tail.Tail) + 1
    printfn "Min rainfall:  %A, %A/%A" min monthMin (int(yearMinList.Head))
    
    
//
// Main:
//
[<EntryPoint>]
let main argv = 
    printfn "** Rainfall Analysis Program **\n"

    //
    //  read entire file as a list of strings:
    //
    let file = ReadFile "rainfall-midway-2.txt"

    //
    // Parse the data in to a list of lists, where
    // each sub-list is [year err value value ...]
    //
    let rainfall = List.map ParseLine file

    //
    // Getting the per year printed out
    //
    let result = RainAverageByYear rainfall
    printfn ""

    //
    // Getting the per month printed out
    //
    let months = ["Jan" ; "Feb" ; "Mar" ; "Apr" ; "May" ; "Jun" ; "Jul" ; "Aug" ; "Sep" ; "Oct" ; "Nov" ; "Dec"]
    let result = RainAverageByMonth rainfall months 1
    printfn ""

    //
    // Finding the max and min rain fall and printing it out
    //
    let result = MaxAndMin rainfall

    //done
    printfn "\n** Done**\n\n"
    0 // return an integer exit code
