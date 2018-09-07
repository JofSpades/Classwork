var page,submit,firstDate,firstStart,firstEnd,secondDate,secondStart,secondEnd,thirdDate,thirdStart,thirdEnd;
// listing of spcific three letter codes for quick refrence into the errors array
var errorName = {
    F3M: 1,//first later than 3 months
    S3M: 2,//second later than 3 months
    T3M: 3,//third later than 3 months
    FSS: 4,//first second same
    FEF: 5,//first time end before start
    SEF: 6,//second time end before start
    TEF: 7,//third time end before start
    FSE: 8,//first start too early
    SSE: 9,//second start too early
    TSE: 10,//third start too early
    FSL: 11,//first start too late
    SSL: 12,//second start too late
    TSL: 13,//third start too late
    FEL: 14,//first end too late
    SEL: 15,//second end too late
    TEL: 16,//third end too late
    FEN: 17,//first enough time
    SEN: 18,//second enough time
    TEN: 19,//third enough time
    FSO: 20,//first too soon
    SSO: 21,//second too soon
    TSO: 22,//third too soon
    FTS: 23,//first third same
    STS: 24,//second third same
    FEE: 25,//first end too early
    SEE: 26,//second end too early
    TEE: 27,//third end too early
};
//array of checks to see if the error has already been set 
var errors = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0];
//list of error strings
var errorStrings = [
    'Request date is too far in advance, please make it sooner than three months',
    'More than one request has been made for the same day',
    'The start time is after the end time',
    'The start time is before 9:00am',
    'The start time is after 4:15pm',
    'The end time is before 10:00am',
    'The end time is after 5:00pm',
    'The start and end times are less than an hour apart',
    'The request is too soon',
];
var elements = [
    'edit-date1-date-datepicker-popup-0',
    'edit-date1-start-timeEntry-popup-0',
    'edit-date1-end-timeEntry-popup-0',
    'edit-date2-date-datepicker-popup-0',
    'edit-date2-start-timeEntry-popup-0',
    'edit-date2-end-timeEntry-popup-0',
    'edit-date3-date-datepicker-popup-0',
    'edit-date3-start-timeEntry-popup-0',
    'edit-date3-end-timeEntry-popup-0',
];
//used to obtain a count of all errors
function hasErrors(element){
    var errorString = '';
    //if cascade grabbing the element and check its individual errors
    if(element == 'edit-date1-date-datepicker-popup-0'){
        if(errors[errorName.F3M] == 1){
            errorString += errorStrings[0]+'<br>';
        }
        if(errors[errorName.FSS] == 1){
            errorString += errorStrings[1]+'<br>';
        }
        if(errors[errorName.FTS] == 1){
            errorString += errorStrings[1]+'<br>';
        }
        if(errors[errorName.FSO] == 1){
            errorString += errorStrings[8]+'<br>';
        }
        return errorString;
    } else if(element == 'edit-date1-start-timeEntry-popup-0'){
        if(errors[errorName.FEF] == 1){
            errorString += errorStrings[2]+'<br>';
        }
        if(errors[errorName.FSE] == 1){
            errorString += errorStrings[3]+'<br>';
        }
        if(errors[errorName.FSL] == 1){
            errorString += errorStrings[4]+'<br>';
        }
        if(errors[errorName.FEN] == 1){
            errorString += errorStrings[7]+'<br>';
        }
        return errorString;
    } else if(element == 'edit-date1-end-timeEntry-popup-0'){
        if(errors[errorName.FEF] == 1){
            errorString += errorStrings[2]+'<br>';
        }
        if(errors[errorName.FEE] == 1){
            errorString += errorStrings[5]+'<br>';
        }
        if(errors[errorName.FEL] == 1){
            errorString += errorStrings[6]+'<br>';
        }
        if(errors[errorName.FEN] == 1){
            errorString += errorStrings[7]+'<br>';
        }
        return errorString;
    } else if(element == 'edit-date2-date-datepicker-popup-0'){
        if(errors[errorName.S3M] == 1){
            errorString += errorStrings[0]+'<br>';
        }
        if(errors[errorName.SSS] == 1){
            errorString += errorStrings[1]+'<br>';
        }
        if(errors[errorName.STS] == 1){
            errorString += errorStrings[1]+'<br>';
        }
        if(errors[errorName.SSO] == 1){
            errorString += errorStrings[8]+'<br>';
        }
        return errorString;
    } else if(element == 'edit-date2-start-timeEntry-popup-0'){
        if(errors[errorName.SEF] == 1){
            errorString += errorStrings[2]+'<br>';
        }
        if(errors[errorName.SSE] == 1){
            errorString += errorStrings[3]+'<br>';
        }
        if(errors[errorName.SSL] == 1){
            errorString += errorStrings[4]+'<br>';
        }
        if(errors[errorName.SEN] == 1){
            errorString += errorStrings[7]+'<br>';
        }
        return errorString;
    } else if(element == 'edit-date2-end-timeEntry-popup-0'){
        if(errors[errorName.SEF] == 1){
            errorString += errorStrings[2]+'<br>';
        }
        if(errors[errorName.SEE] == 1){
            errorString += errorStrings[5]+'<br>';
        }
        if(errors[errorName.SEL] == 1){
            errorString += errorStrings[6]+'<br>';
        }
        if(errors[errorName.SEN] == 1){
            errorString += errorStrings[7]+'<br>';
        }
        return errorString;
    } else if(element == 'edit-date3-date-datepicker-popup-0'){
        if(errors[errorName.T3M] == 1){
            errorString += errorStrings[0]+'<br>';
        }
        if(errors[errorName.TSS] == 1){
            errorString += errorStrings[1]+'<br>';
        }
        if(errors[errorName.TTS] == 1){
            errorString += errorStrings[1]+'<br>';
        }
        if(errors[errorName.TSO] == 1){
            errorString += errorStrings[8]+'<br>';
        }
        return errorString;
    } else if(element == 'edit-date3-start-timeEntry-popup-0'){
        if(errors[errorName.TEF] == 1){
            errorString += errorStrings[2]+'<br>';
        }
        if(errors[errorName.TSE] == 1){
            errorString += errorStrings[3]+'<br>';
        }
        if(errors[errorName.TSL] == 1){
            errorString += errorStrings[4]+'<br>';
        }
        if(errors[errorName.TEN] == 1){
            errorString += errorStrings[7]+'<br>';
        }
        return errorString;
    } else if(element == 'edit-date3-end-timeEntry-popup-0'){
        if(errors[errorName.TEF] == 1){
            errorString += errorStrings[2]+'<br>';
        }
        if(errors[errorName.TEE] == 1){
            errorString += errorStrings[5]+'<br>';
        }
        if(errors[errorName.TEL] == 1){
            errorString += errorStrings[6]+'<br>';
        }
        if(errors[errorName.TEN] == 1){
            errorString += errorStrings[7]+'<br>';
        }
        return errorString;
    }
    return errorString;
}
//setup of every variable and connection of the eventhandlers
window.onload = function(){
    firstDate = document.getElementById('edit-date1-date-datepicker-popup-0');
    firstStart = document.getElementById('edit-date1-start-timeEntry-popup-0');
    firstEnd = document.getElementById('edit-date1-end-timeEntry-popup-0');
    secondDate = document.getElementById('edit-date2-date-datepicker-popup-0');
    secondStart = document.getElementById('edit-date2-start-timeEntry-popup-0');
    secondEnd = document.getElementById('edit-date2-end-timeEntry-popup-0');
    thirdDate = document.getElementById('edit-date3-date-datepicker-popup-0');
    thirdStart = document.getElementById('edit-date3-start-timeEntry-popup-0');
    thirdEnd = document.getElementById('edit-date3-end-timeEntry-popup-0');
    submit = document.getElementById('edit-submit');
    page = document.getElementById('page');
    //page events
    page.addEventListener('click', dateChecks, true);
    page.addEventListener('keypres', dateChecks, true);
    page.addEventListener('click', timeChecks, true);
    page.addEventListener('keypres', timeChecks, true);
    //firstDate events
    firstDate.addEventListener('click', dateChecks, true);
    firstDate.addEventListener('keypres', dateChecks, true);
    firstDate.addEventListener('click', timeChecks, true);
    firstDate.addEventListener('keypres', timeChecks, true);
    //firstStart events
    firstStart.addEventListener('click', dateChecks, true);
    firstStart.addEventListener('keypres', dateChecks, true);
    firstStart.addEventListener('click', timeChecks, true);
    firstStart.addEventListener('keypres', timeChecks, true);
    //firstEnd events
    firstEnd.addEventListener('click', dateChecks, true);
    firstEnd.addEventListener('keypres', dateChecks, true);
    firstEnd.addEventListener('click', timeChecks, true);
    firstEnd.addEventListener('keypres', timeChecks, true);
    //secondDate events
    secondDate.addEventListener('click', dateChecks, true);
    secondDate.addEventListener('keypres', dateChecks, true);
    secondDate.addEventListener('click', timeChecks, true);
    secondDate.addEventListener('keypres', timeChecks, true);
    //secondStart events
    secondStart.addEventListener('click', dateChecks, true);
    secondStart.addEventListener('keypres', dateChecks, true);
    secondStart.addEventListener('click', timeChecks, true);
    secondStart.addEventListener('keypres', timeChecks, true);
    //secondEnd events
    secondEnd.addEventListener('click', dateChecks, true);
    secondEnd.addEventListener('keypres', dateChecks, true);
    secondEnd.addEventListener('click', timeChecks, true);
    secondEnd.addEventListener('keypres', timeChecks, true);
    //thirdDate events
    thirdDate.addEventListener('click', dateChecks, true);
    thirdDate.addEventListener('keypres', dateChecks, true);
    thirdDate.addEventListener('click', timeChecks, true);
    thirdDate.addEventListener('keypres', timeChecks, true);
    //thirdStart events
    thirdStart.addEventListener('click', dateChecks, true);
    thirdStart.addEventListener('keypres', dateChecks, true);
    thirdStart.addEventListener('click', timeChecks, true);
    thirdStart.addEventListener('keypres', timeChecks, true);
    //thirdEnd events
    thirdEnd.addEventListener('click', dateChecks, true);
    thirdEnd.addEventListener('keypres', dateChecks, true);
    thirdEnd.addEventListener('click', timeChecks, true);
    thirdEnd.addEventListener('keypres', timeChecks, true);
};
//only here to make sure that the page is refreshed with js on every load up
window.onunload = function(){};
//converts the supplied time string to an int representing minutes
function convertToUseable(str){
    var time;
    (str.includes("pm"))?(time = 720):(time = 0);
    if(str.substring(0,2) != '12'){
        time += parseInt(str.substring(0,2))*60;
    }
    time += parseInt(str.substring(3,5));
    return time;
}
//converts date string to days since 1/1/0000 assuming MM/DD/YYYY
function convertToDays(str){
    var date = 0;
    date += parseInt(str.substring(6,10))*365.25;
    date += parseInt(str.substring(3,5));
    switch(parseInt(str.substring(0,2))){
        case 12:
            date += 30;
        case 11:
            date += 31;
        case 10:
            date += 30;
        case 9:
            date += 31;
        case 8:
            date += 31;
        case 7:
            date += 30;
        case 6:
            date += 31;
        case 5:
            date += 30;
        case 4:
            date += 31;
        case 3:
            date += 28;
        case 2:
            date += 31;
        default:
            break;
    }
    return date;
}
//locats and sets a new div tag with the list of errors
function inlineMsg(error) {
    var msg;
    var msgcontent;
    var targetdiv = document.getElementById(error);
    if(!document.getElementById('msg' + error)) {
        msg = document.createElement('div');
        msg.id = 'msg' + error;
        msgcontent = document.createElement('div');
        msgcontent.id = 'msgcontent' + error;
        document.body.appendChild(msg);
        msg.appendChild(msgcontent);
        msg.style.filter = 'alpha(opacity=0)';
        msg.style.opacity = 0;
        msg.alpha = 0;
        msg.style.position = 'absolute';
        msg.style.display = 'none';
        msg.style.zIndex = '200';
        msg.style.paddingLeft = '7px';
        msgcontent.style.display = 'block';
        msgcontent.style.background = '#f3e6e6';
        msgcontent.style.border = 'thick solid red';
        msgcontent.style.padding = '5px';
        msgcontent.style.minWidth = '150px';
        msgcontent.style.maxWidth = '750px';
    } else {
        msg = document.getElementById('msg' + error);
        msgcontent = document.getElementById('msgcontent'+error);
    }
    msgcontent.innerHTML = hasErrors(error);
    if(msgcontent.innerHTML != ''){
        msgcontent.innerHTML = msgcontent.innerHTML.substring(0, msgcontent.innerHTML.length - 4);
        targetdiv.style.border = 'thick solid red';
    }
    msg.style.display = 'block';
    var msgheight = msg.offsetHeight;
    var targetheight = targetdiv.offsetHeight;
    var targetwidth = targetdiv.offsetWidth;
    var topposition = topPosition(targetdiv) - ((msgheight - targetheight) / 2);
    var leftposition = leftPosition(targetdiv) + targetwidth + 3;
    msg.style.top = topposition + 'px';
    msg.style.left = leftposition + 'px';
    msg.style.filter = 'alpha(opacity=100)';
    msg.style.opacity = 1.0;
    if(errors.indexOf(1,1) != -1){
        submit.disabled = true;
    }
}
//removes the inline error of a certain kind
//so if more than one error is on a field only one will be removed and leave the 
//div tag until all are removed
function removeInline(error){
    var msg;
    var msgcontent;
    if(document.getElementById('msg'+error)){
        msg = document.getElementById('msg'+error);
        msgcontent = document.getElementById('msgcontent'+error);
        msgcontent.innerHTML = hasErrors(error);
        if(msgcontent.innerHTML != ''){
            msgcontent.innerHTML = msgcontent.innerHTML.substring(0, msgcontent.innerHTML.length - 4);
        }
        if(msgcontent.innerHTML == ''){
            msg.style.opacity = 0.0;
            msg.style.filter = 'alpha(opacity=0)';
            var targetdiv = document.getElementById(error);
            targetdiv.style.border = '';
            targetdiv.style.border = 'thin solid none';
        }
    }
    if(errors.indexOf(1,1) == -1){
        submit.disabled = false;
    }
}
//finds the left side of the field getting an error
function leftPosition(target) {
    var left = 0;
    if(target.offsetParent) {
        while(1) {
            left += target.offsetLeft;
            if(!target.offsetParent) {
                break;
            }
            target = target.offsetParent;
        }
    } else if(target.x){
        left += target.x;
    }
    return left;
}
//finds the top of the field getting an error
function topPosition(target) {
    var top = 0;
    if(target.offsetParent) {
        while(1) {
            top += target.offsetTop;
            if(!target.offsetParent) {
                break;
            }
            target = target.offsetParent;
        }
    } else if(target.y){
        top += target.y;
    }
    return top;
}
//all the checks preformed on the dates
function dateChecks(){
    var threeMonthsFromNow = moment().add(3, 'month').format('MM/DD/YYYY');
    var tomorrow = moment().add(1,'day').format('MM/DD/YYYY');
    tomorrow = convertToDays(tomorrow);
    threeMonthsFromNow = convertToDays(threeMonthsFromNow);
    var firstValue = convertToDays(firstDate.value);
    if(threeMonthsFromNow < firstValue){
        if(errors[errorName.F3M] == 0){
            errors[errorName.F3M] = 1;
            inlineMsg(elements[0]);
        }
    } else {
        errors[errorName.F3M] = 0;
        removeInline(elements[0]);
    }
    var secondValue = convertToDays(secondDate.value);
    if(threeMonthsFromNow < secondValue){
        if(errors[errorName.S3M] == 0){
            errors[errorName.S3M] = 1;
            inlineMsg(elements[3]);
        }
    } else {
        errors[errorName.S3M] = 0;
        removeInline(elements[3]);
    }
    var thirdValue = convertToDays(thirdDate.value);
    if(threeMonthsFromNow < thirdValue){
        if(errors[errorName.T3M] == 0){
            errors[errorName.T3M] = 1;
            inlineMsg(elements[6]);
        }
    } else {
        errors[errorName.T3M] = 0;
        removeInline(elements[6]);
    }
    if(tomorrow > firstValue){
        if(errors[errorName.FSO] == 0){
            errors[errorName.FSO] = 1;
            inlineMsg(elements[0]);
        }
    } else {
        errors[errorName.FSO] = 0;
        removeInline(elements[0]);
    }
    if(tomorrow > secondValue){
        if(errors[errorName.SSO] == 0){
            errors[errorName.SSO] = 1;
            inlineMsg(elements[3]);
        }
    } else {
        errors[errorName.SSO] = 0;
        removeInline(elements[3]);
    }
    if(tomorrow > thirdValue){
        if(errors[errorName.TSO] == 0){
            errors[errorName.TSO] = 1;
            inlineMsg(elements[6]);
        }
    } else {
        errors[errorName.TSO] = 0;
        removeInline(elements[6]);
    }
    if(firstValue == secondValue){
        if(errors[errorName.FSS] == 0){
            errors[errorName.FSS] = 1;
            inlineMsg(elements[0]);
            inlineMsg(elements[3]);
        }
    } else {
        errors[errorName.FSS] = 0;
        removeInline(elements[0]);
        removeInline(elements[3]);
    }
    if(firstValue == thirdValue){
        if(errors[errorName.FTS] == 0){
            errors[errorName.FTS] = 1;
            inlineMsg(elements[0]);
            inlineMsg(elements[6]);
        }
    } else {
        errors[errorName.FTS] = 0;
        removeInline(elements[0]);
        removeInline(elements[6]);
    }
    if(thirdValue == secondValue){
        if(errors[errorName.STS] == 0){
            errors[errorName.STS] = 1;
            inlineMsg(elements[3]);
            inlineMsg(elements[6]);
        }
    } else {
        errors[errorName.STS] = 0;
        removeInline(elements[3]);
        removeInline(elements[6]);
    }
}
// checks if the first supplied time occurs before the second one
function oneBeforeTwo(timeOne, timeTwo){
    if(convertToUseable(timeOne) >= convertToUseable(timeTwo)){
        return false;
    }
    return true;
}
//checks if the supplied start time is too early, before 9:00am
function startTooEarly(str){
    if(convertToUseable(str) < convertToUseable("9:00am")){
        return true;
    }
    return false;
}
//checks if the supplied start time is too late, after 4:15pm
function startTooLate(str){
    if(convertToUseable(str) > 975){
        return true;
    }
    return false;
}
//checks if the supplied end time is too late, after 5:00pm
function endTooLate(str){
    //1020 is the number of minutes seince 12:00AM-5:00PM 
    if(convertToUseable(str) > 1020){
        return true;
    }
    return false;
}
//checks if the supplied end time is too early, before 10:00am
function endTooEarly(str){
    if(convertToUseable(str) < convertToUseable("10:00am")){
        return true;
    }
    return false;
}
//checks that the two supplied times are at least an hour appart
function enoughTime(str1, str2){
    var timeInBetween = convertToUseable(str2) - convertToUseable(str1);
    if(timeInBetween < 60){
        return false;
    }
    return true;
}
//used to preform all of the checks on the individual time elements
//blocked together so that there is the most dynamic reaction to error checking
function timeChecks(){
    if(oneBeforeTwo(firstEnd.value,firstStart.value)){
        errors[errorName.FEF] = 1;
        inlineMsg(elements[1]);
        inlineMsg(elements[2]);
    } else {
        errors[errorName.FEF] = 0;
        removeInline(elements[1]);
        removeInline(elements[2]);
    }
    if(oneBeforeTwo(secondEnd.value,secondStart.value)){
        errors[errorName.SEF] = 1;
        inlineMsg(elements[4]);
        inlineMsg(elements[5]);
    } else {
        errors[errorName.SEF] = 0;
        removeInline(elements[4]);
        removeInline(elements[5]);
    }
    if(oneBeforeTwo(thirdEnd.value,thirdStart.value)){
        errors[errorName.TEF] = 1;
        inlineMsg(elements[7]);
        inlineMsg(elements[8]);
    } else {
        errors[errorName.TEF] = 0;
        removeInline(elements[7]);
        removeInline(elements[8]);
    }
    if(startTooEarly(firstStart.value)){
        errors[errorName.FSE] = 1;
        inlineMsg(elements[1])
    } else {
        errors[errorName.FSE] = 0;
        removeInline(elements[1]);
    }
    if(startTooEarly(secondStart.value)){
        errors[errorName.SSE] = 1;
        inlineMsg(elements[4]);
    } else {
        errors[errorName.SSE] = 0;
        removeInline(elements[4]);
    }
    if(startTooEarly(thirdStart.value)){
        errors[errorName.TSE] = 1;
        inlineMsg(elements[7]);
    } else {
        errors[errorName.TSE] = 0;
        removeInline(elements[7]);
    }
    if(startTooLate(firstStart.value)){
        errors[errorName.FSL] = 1;
        inlineMsg(elements[1]);
    } else {
        errors[errorName.FSL] = 0;
        removeInline(elements[1]);
    }
    if(startTooLate(secondStart.value)){
        errors[errorName.SSL] = 1;
        inlineMsg(elements[4]);
    } else {
        errors[errorName.SSL] = 0;
        removeInline(elements[4]);
    }
    if(startTooLate(thirdStart.value)){
        errors[errorName.TSL] = 1;
        inlineMsg(elements[7]);
    } else {
        errors[errorName.TSL] = 0;
        removeInline(elements[7]);
    }
    if(endTooLate(firstEnd.value)){
        errors[errorName.FEL] = 1;
        inlineMsg(elements[2]);
    } else {
        errors[errorName.FEL] = 0;
        removeInline(elements[2]);
    }
    if(endTooLate(secondEnd.value)){
        errors[errorName.SEL] = 1;
        inlineMsg(elements[5]);
    } else {
        errors[errorName.SEL] = 0;
        removeInline(elements[5]);
    }
    if(endTooLate(thirdEnd.value)){
        errors[errorName.TSL] = 1;
        inlineMsg(elements[8]);
    } else {
        errors[errorName.TSL] = 0;
        removeInline(elements[8]);
    }
    if(endTooEarly(firstEnd.value)){
        errors[errorName.FEE] = 1;
        inlineMsg(elements[2]);
    } else {
        errors[errorName.FEE] = 0;
        removeInline(elements[2]);
    }
    if(endTooEarly(secondEnd.value)){
        errors[errorName.SEE] = 1;
        inlineMsg(elements[5]);
    } else {
        errors[errorName.SEE] = 0;
        removeInline(elements[5]);
    }
    if(endTooEarly(thirdEnd.value)){
        errors[errorName.TEE] = 1;
        inlineMsg(elements[8]);
    } else {
        errors[errorName.TEE] = 0;
        removeInline(elements[8]);
    }
    if(!enoughTime(firstStart.value, firstEnd.value)){
        errors[errorName.FEN] = 1;
        inlineMsg(elements[1]);
        inlineMsg(elements[2]);
    } else {
        errors[errorName.FEN] = 0;
        removeInline(elements[1]);
        removeInline(elements[2]);
    }
    if(!enoughTime(secondStart.value, secondEnd.value)){
        errors[errorName.SEN] = 1;
        inlineMsg(elements[4]);
        inlineMsg(elements[5]);
    } else {
        errors[errorName.SEN] = 0;
        removeInline(elements[4]);
        removeInline(elements[5]);
    }
    if(!enoughTime(thirdStart.value, thirdEnd.value)){
        errors[errorName.TEN] = 1;
        inlineMsg(elements[7]);
        inlineMsg(elements[8]);
    } else {
        errors[errorName.TEN] = 0;
        removeInline(elements[7]);
        removeInline(elements[8]);
    }
}
