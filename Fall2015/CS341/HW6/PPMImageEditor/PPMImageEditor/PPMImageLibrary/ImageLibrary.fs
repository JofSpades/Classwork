//
// F#-based PPM image library.
//
// Maxwell Petersen
// U. of Illinois, Chicago
// CS341, Fall 2015
// Homework 6
//

module PPMImageLibrary

#light


//
// DebugOutput:
//
// Outputs to console, which appears in the "Output" window pane of
// Visual Studio when you run with debugging (F5).
//
let rec private OutputImage(image:int list list) = 
    if image = [] then
        printfn "**END**"
    else
        printfn "%A" image.Head
        OutputImage(image.Tail)
           
let DebugOutput(width:int, height:int, depth:int, image:int list list) =
    printfn "**HEADER**"
    printfn "W=%A, H=%A, D=%A" width height depth
    printfn "**IMAGE**"
    OutputImage(image)


//
// TransformFirstRowWhite:
//
// An example transformation: replaces the first row of the given image
// with a row of all white pixels.
//
let rec BuildRowOfWhite cols white = 
  if cols = 0 then
    []
  else 
    // 1 pixel, i.e. RGB value, followed by remaining pixels:
    white :: white :: white :: BuildRowOfWhite (cols-1) white

let FirstRowWhite(width:int, height:int, depth:int, image:int list list) = 
    // first row all white :: followed by rest of original image
    (BuildRowOfWhite width depth) :: image.Tail

//
// Converting the int list list to a string list list
//
let rec P3ToStringLine (intList: int list) = 
    match intList with
    | [l] -> l.ToString()
    | head :: tail -> head.ToString() + " " + P3ToStringLine tail
    | [] -> ""

let rec P3ToString (intListList: int list list)=
    match intListList with
    | [] -> []
    | _ -> (P3ToStringLine intListList.Head) :: P3ToString intListList.Tail    

//
// WriteP3Image:
//
// Writes the given image out to a text file, in "P3" format.  Returns true if successful,
// false if not.
//
let rec WriteP3Image(filepath:string, width:int, height:int, depth:int, image:int list list) = 
    //
    // Here's one possible strategy: build a list of strings, then WriteAllLines.
    // Each string appears on a separate line. 
    //
  
    let L = P3ToString image
    System.IO.File.WriteAllLines(filepath, L)
  
    true  // success

//
// finds the average of the RGB at a time then concats to form a new list
//
let rec _GrayscaleAverage (inList: int list) =
    match inList with
    | [] -> []
    | red :: green :: blue :: tail -> int(List.average [double(red); double(green); double(blue)]) :: int(List.average [double(red); double(green); double(blue)]) :: int(List.average [double(red); double(green); double(blue)]) :: _GrayscaleAverage tail
    | _ -> []



let rec GrayscaleAverage (inListList: int list list) = 
    match inListList with
    | [] -> []
    | _ -> _GrayscaleAverage inListList.Head :: GrayscaleAverage inListList.Tail


let rec Grayscale(width:int, height:int, depth:int, image:int list list) = 
    let outListList = GrayscaleAverage image
    outListList

//
// Applies the threshold to all of the RGB values
//
let rec ThresholdSetter (inListList: int list list) threshold = 
    if inListList = [] then
        []
    else 
        List.map (fun value -> if value > threshold then 255 else 0 ) (inListList.Head) :: ThresholdSetter inListList.Tail threshold
 

let rec Threshold(width:int, height:int, depth:int, image:int list list, threshold:int) = 
    let outListList = ThresholdSetter image threshold
    outListList

//
// Flip the given picture along the vertial axis
//
let rec FlipHorizontalEngine (inList: int list, width: int) = 
    if width = 0 then
        []
    else
        List.nth inList ((3 * width) - 3) :: List.nth inList ((3 * width) - 2) :: List.nth inList ((3 * width) - 1) :: FlipHorizontalEngine (inList, width - 1)

let rec FlipHorizontal(width:int, height:int, depth:int, image:int list list) = 
    if image = [] then
        []
    else
        (FlipHorizontalEngine (image.Head, width)) :: (FlipHorizontal (width, height, depth, image.Tail))

//
// Expand the ppm file by a given factor
//
let rec ZoomEngine (inList: int list, factor:int) = 
    if inList = [] then
        []
    elif factor = 4 then
        match inList with
        | [] -> []
        | r :: g :: b :: tail -> r :: g :: b :: r :: g :: b :: r :: g :: b :: r :: g :: b :: ZoomEngine (tail, factor)
        | _ -> []
    elif factor = 3 then
        match inList with
        | [] -> []
        | r :: g :: b :: tail -> r :: g :: b :: r :: g :: b :: r :: g :: b :: ZoomEngine (tail, factor)
        | _ -> []
    elif factor = 2 then
        match inList with
        | [] -> []
        | r :: g :: b :: tail -> r :: g :: b :: r :: g :: b :: ZoomEngine (tail, factor)
        | _ -> []
    else
        inList

let rec Zoom(width:int, height:int, depth:int, image:int list list, factor:int) = 
    if image = [] then
        []
    elif factor = 4 then
        let zoomed = ZoomEngine (image.Head, factor)
        zoomed :: zoomed :: zoomed :: zoomed :: Zoom (width, height, depth, image.Tail, factor)
    elif factor = 3 then
        let zoomed = ZoomEngine (image.Head, factor)
        zoomed :: zoomed :: zoomed :: Zoom (width, height, depth, image.Tail, factor)
    elif factor = 2 then
        let zoomed = ZoomEngine (image.Head, factor)
        zoomed :: zoomed :: Zoom (width, height, depth, image.Tail, factor)
    else
        image

//
// Rotate to the right by 90 degrees
//
let rec RotateEngineRow (width:int, heigth:int, image:int list list, col:int, row:int) =
    if row = heigth then
        []
    else
        let neededRow = List.nth image ((heigth - 1) - row)
        List.nth neededRow col :: List.nth neededRow (col + 1) :: List.nth neededRow (col + 2) :: RotateEngineRow (width, heigth, image, col, row + 1)

let rec RotateEngineCol (width:int, heigth:int, image: int list list, row:int, col:int) =
    if col = (3 * width) then
        []
    else
        RotateEngineRow (width, heigth, image, col, row) :: RotateEngineCol (width, heigth, image, row, 3 + col)

let rec RotateRight90(width:int, height:int, depth:int, image:int list list) = 
    let outListList = RotateEngineCol (width, height, image, 0, 0)
    outListList