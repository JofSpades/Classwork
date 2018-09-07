<?php
function oss_client_oss_general_request_form($form, &$form_state) {
    global $user;
    if(!isset($_SESSION['shib_auth_username'])){
        drupal_goto('/');
    }
    $client = checkIfClient($_SESSION['shib_auth_username'].'@uic.edu');
    if($client  == ''){
        drupal_goto('/oss_non_client/form');
    }
    //the array entry is the dptid of the client whome logged in
    $images = array(
        0 => '/sites/all/modules/custom/oss_request/images/ADM.OVCA.LOCKB.SM.BLK.PNG',
        5 => '/sites/all/modules/custom/oss_request/images/ADM.CHAN.ACEQ.CTT.SM.BLK.PNG',
    );
    $form['#attached']['js'] = array(
        drupal_get_path('module','oss_request').'/moment.js',
        drupal_get_path('module','oss_request').'/oss_javascript.js',
    );
    if($client['dptid'] < 1000){
        $form['logo'] = array(
            '#type' => 'item',
            '#markup' => '<img src="'.$images[$client['dptid']].'" style="width:200px;height:150px>',
        );
    }
    $form['greeting'] = array(
        '#type' => 'item',
        '#markup' => '</br>'.t('Hello ').$client['name'].','.'</br>'.t('Thank you for using On-Site Support.').'</br>'.t('Please fill out the information below and we will get back to you within 4 hours of your request submission.').'</br>',
    );
    $date = date('Y-m-d H:i:s');
    $date = new DateTime($date);
    $date_format = 'm/d/Y';
    $time_format = 'h:ia';
    $weekend = array('Sun' => '','Sat' => '');
    $nextDay = clone $date;
    $i = 0;
    $nextDates = array();
    while ($i < 3){
        $nextDay->add(new DateInterval('P1D'));
        if (isset($weekend[$nextDay->format('D')])) continue;
        $nextDates[] = $nextDay->format('Y-m-d H:i:s');
        $i++;
    }
    $form['date1'] = array(
        '#type' => 'fieldset',
        '#title' => t('First Service Request Time'),
        '#description' => t('Please only select days and times at least one day from now between the hours of 9:00AM-5:00PM, and only one time selection can be made per day'),
    );
    $form['date1']['date1_date'] = array(
        '#type' => 'date_popup',
        '#default_value' => $nextDates[0],
        '#date_type' => DATE_DATETIME,
        '#date_format' => $date_format,
        '#date_increment' => 1,
        '#dateonly' => TRUE,
    );
    $form['date1']['date1_start'] = array(
        '#type' => 'date_popup',
        '#default_value' => $nextDates[0],
        '#date_type' => DATE_DATETIME,
        '#date_format' => $time_format,
        '#date_increment' => 15,
        '#title' => t('Start'),
        '#timeonly' => TRUE,
    );
    $form['date1']['date1_end'] = array(
        '#type' => 'date_popup',
        '#default_value' => $nextDates[0],
        '#date_type' => DATE_DATETIME,
        '#date_format' => $time_format,
        '#date_increment' => 15,
        '#title' => t('End'),
        '#timeonly' => TRUE,
    );
    $form['date2'] = array(
        '#type' => 'fieldset',
        '#title' => t('Second Service Request Time'),
        '#description' => t('Please only select days and times at least one day from now between the hours of 9:00AM-5:00PM, and only one time selection can be made per day'),
    );
    $form['date2']['date2_date'] = array(
        '#type' => 'date_popup',
        '#default_value' => $nextDates[1],
        '#date_type' => DATE_DATETIME,
        '#date_format' => $date_format,
        '#date_increment' => 1,
        '#dateonly' => TRUE,
    );
    $form['date2']['date2_start'] = array(
        '#type' => 'date_popup',
        '#default_value' => $nextDates[1],
        '#date_type' => DATE_DATETIME,
        '#date_format' => $time_format,
        '#date_increment' => 15,
        '#timeonly' => TRUE,
        '#title' => t('Start'),
    );
    $form['date2']['date2_end'] = array(
        '#type' => 'date_popup',
        '#default_value' => $nextDates[1],
        '#date_type' => DATE_DATETIME,
        '#date_format' => $time_format,
        '#date_increment' => 15,
        '#timeonly' => TRUE,
        '#title' => t('End'),
    );
    $form['date3'] = array(
        '#type' => 'fieldset',
        '#title' => t('Third Service Request Time'),
        '#description' => t('Please only select days and times at least one day from now between the hours of 9:00AM-5:00PM, and only one time selection can be made per day'),
    );
    $form['date3']['date3_date'] = array(
        '#type' => 'date_popup',
        '#default_value' => $nextDates[2],
        '#date_type' => DATE_DATETIME,
        '#date_format' => $date_format,
        '#date_increment' => 1,
        '#dateonly' => TRUE,
    );
    $form['date3']['date3_start'] = array(
        '#type' => 'date_popup',
        '#default_value' => $nextDates[2],
        '#date_type' => DATE_DATETIME,
        '#date_format' => $time_format,
        '#date_increment' => 15,
        '#title' => t('Start'),
        '#timeonly' => TRUE,
    );
    $form['date3']['date3_end'] = array(
        '#type' => 'date_popup',
        '#default_value' => $nextDates[2],
        '#date_type' => DATE_DATETIME,
        '#date_format' => $time_format,
        '#date_increment' => 15,
        '#title' => t('End'),
        '#timeonly' => TRUE,
    );
    $form['machine_type'] = array(
        '#type' => 'fieldset',
        '#title' => t('Machine Type'),
    );
    $form['machine_type']['machine_types'] = array(
        '#type' => 'checkboxes',
        '#options' => array(
            'machine_wlaptop' => t('Windows Laptop'),
            'machine_wdesktop' => t('Windows Desktop'),
            'machine_alaptop' => t('Apple Laptop'),
            'machine_adesktop' => t('Apple Desktop'), 
            'machine_tablet' => t('Tablet (i.e. Microsoft Surface)'),
            'machine_printer' => t('Printer'),),
    );
    $form['machine_type']['other_machine'] = array(
        '#type' => 'textfield',
        '#title' => t('Other'),
    );
    $form['problem_type'] = array(
        '#type' => 'fieldset',
        '#title' => t('Problem Type'),
    );
    $form['problem_type']['hardware'] = array(
        '#type' => 'fieldset',
        '#title' => t('Hardware'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
    );
    $form['problem_type']['hardware']['hardware_types'] = array(
        '#type' => 'checkboxes',
        '#options' => array(
            'hardware_drive' => t('Hard Drive'),
            'hardware_video' => t('Video Display'),
            'hardware_peripherals' => t('Peripherals'),),
    );
    $form['problem_type']['hardware']['other_hardware'] = array(
        '#type' => 'textfield',
        '#title' => t('Other'),
    );
    $form['problem_type']['internet'] = array(
        '#type' => 'fieldset',
        '#title' => t('Internet'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
    );
    $form['problem_type']['internet']['internet_types'] = array(
        '#type' => 'checkboxes',
        '#options' => array(
            'internet_connection' => t('Connectivity issues'),),
    );
    $form['problem_type']['internet']['other_internet'] = array(
        '#type' => 'textfield',
        '#title' => t('Other'),
    );
    $form['problem_type']['migration'] = array(
        '#type' => 'fieldset',
        '#title' => t('Migration'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
    );
    $form['problem_type']['migration']['migration_types'] = array(
        '#type' => 'checkboxes',
        '#options' => array(
            'migration_account' => t('Account'),
            'migration_data' => t('Data'),
            'migration_office' => t('Office/Location'),),
    );
    $form['problem_type']['nas_server'] = array(
        '#type' => 'fieldset',
        '#title' => t('NAS/Server'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
    );
    $form['problem_type']['nas_server']['nas_other'] = array(
        '#type' => 'textfield',
        '#title' => t('Other'),
    );
    $form['problem_type']['new_user_computer'] = array(
        '#type' => 'fieldset',
        '#title' => t('New User/Computer'),
        '#collapsible' => TRUE,
        '#collapsed'=> TRUE,
    );
    $form['problem_type']['new_user_computer']['new_user_computer_types'] = array(
        '#type' => 'checkboxes',
        '#options' => array(
            'new_computer' => t('Computer set-up'),
            'new_image' => t('Re-image'),
            'new_upgrade' => t('Upgrade'),),
    );
    $form['problem_type']['phones'] = array(
        '#type' => 'fieldset',
        '#title' => t('Phones'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
        '#description' => t('Please direct any phone issues to Pat Wongchinsri at patchare@uic.edu or 3-3390.'),
    );
    $form['problem_type']['printer'] = array(
        '#type' => 'fieldset',
        '#title' => t('Printers'),
        '#collapsible' =>TRUE,
        '#collapsed' => TRUE,
    );
    $form['problem_type']['printer']['printer_types'] = array(
        '#type' => 'checkboxes',
        '#options' => array(
            'printer_connection' =>t('Connectivity'),
            'printer_jams' => t('Jams'),),
    );
    $form['problem_type']['printer']['other_printer'] = array(
        '#type' => 'textfield',
        '#title' => t('Other'),
    );
    $form['problem_type']['recovery'] = array(
        '#type' => 'fieldset',
        '#title' => t('Recovery'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
    );
    $form['problem_type']['recovery']['recovery_types'] = array(
        '#type' => 'checkboxes',
        '#options' => array(
            'recovery_password' => t('Password'),
            'recovery_date' => t('Data*'),
            'recovery_bit' =>t('Bit Locker'),),
        '#description' => t('*We will make one attempt on retreaving the data but there is no guarentee of success.'),
    );
    $form['problem_type']['software'] = array(
        '#type' => 'fieldset',
        '#title' => t('Software'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
    );
    $form['problem_type']['software']['software_types'] = array(
        '#type' => 'checkboxes',
        '#options' => array(
            'software_install' => t('Install request*'),
            'software_microsoft' => t('Microsoft Office'),
            //'software_pinnacle' => t('Pinnacle, Banner'),
            'software_web' => t('Web browsers'),),
        '#description' => t('*If the product is not freely available from the WebStore, please have a copy of the software available for us to install for you, and specify the exact software in the "Other" box below'),
    );
    $form['problem_type']['software']['other_software'] = array(
        '#type' => 'textfield',
        '#title' => t('Other'),
    );
    $form['problem_type']['other_problem'] = array(
        '#type' => 'textfield',
        '#title' => t('Other Type of Problem'),
    );
    $form['problem_type']['extra_info'] = array(
        '#type' => 'textarea',
        '#title' => t('Extra Explanation'),
        '#maxLength' => 32767,
    );
    $form['acknowledgement'] = array(
        '#type' => 'radios',
        '#title' => t('I understand that I am requesting a fee-based service to resolve the problem I are experiencing, and I have first contacted my department\'s REACH IT contact for support.  I have also received permission from my department\'s business manager to request a billable service, and will provide a C-FOAP account code to charge against when it is requested.'),
        '#default_value' => NULL,
        '#options' => array(0 => 'Acknowledged'),
        '#required' => TRUE,
    );
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => 'Submit',
    );
    return $form;
}
function oss_client_oss_general_request_form_validate($form, &$form_state){
    if(array_search('software_install', array_filter($form_state['values']['software_types'])) && $form_state['values']['other_software'] == ""){
        form_set_error('software install', 'You need to provide us with the software you want installed');
    }
    $date_one_date = $form_state['values']['date1_date'];
    $date_one_start = $form_state['values']['date1_start'];
    $date_one_end = $form_state['values']['date1_end'];
    $date_two_date = $form_state['values']['date2_date'];
    $date_two_start = $form_state['values']['date2_start'];
    $date_two_end = $form_state['values']['date2_end'];
    $date_three_date = $form_state['values']['date3_date'];
    $date_three_start = $form_state['values']['date3_start'];
    $date_three_end = $form_state['values']['date3_end'];
    //machine type
    $machine_types = array(
        $form_state['values']['machine_types']['machine_wlaptop'],
        $form_state['values']['machine_types']['machine_wdesktop'],
        $form_state['values']['machine_types']['machine_alaptop'],
        $form_state['values']['machine_types']['machine_adesktop'],
        $form_state['values']['machine_types']['machine_tablet'],
        $form_state['values']['machine_types']['machine_printer'],
    );
    $other_machine = $form_state['values']['other_machine'];
    //problem types
    $problem_types = array(
        $form_state['values']['hardware_types']['hardware_drive'],
        $form_state['values']['hardware_types']['hardware_video'],
        $form_state['values']['hardware_types']['hardware_peripherals'],
        $form_state['values']['internet_types']['internet_connection'],
        $form_state['values']['migration_types']['migration_account'],
        $form_state['values']['migration_types']['migration_data'],
        $form_state['values']['migration_types']['migration_office'],
        $form_state['values']['new_user_computer_types']['new_computer'],
        $form_state['values']['new_user_computer_types']['new_image'],
        $form_state['values']['new_user_computer_types']['new_upgrade'],
        $form_state['values']['printer_types']['printer_connection'],
        $form_state['values']['printer_types']['printer_jams'],
        $form_state['values']['recovery_types']['recovery_password'],
        $form_state['values']['recovery_types']['recovery_date'],
        $form_state['values']['recovery_types']['recovery_bit'],
        $form_state['values']['software_types']['software_install'],
        $form_state['values']['software_types']['software_microsoft'],
        $form_state['values']['software_types']['software_web'],
    );
    $problem_other = array(
        $form_state['values']['other_hardware'],
        $form_state['values']['other_internet'],
        $form_state['values']['nas_other'],
        $form_state['values']['other_printer'],
        $form_state['values']['other_software'],
        $form_state['values']['other_problem'],
        $form_state['values']['extra_info'],
    );
    if(request_too_soon($date_one_date)){
        form_set_error('date_one_date' ,'First request day too soon, please allow at least one business day in advance for the service request. If we are able to we will try to accomidate a more urgent matter to be adressed sooner.');
    }
    if(request_too_soon($date_two_date)){
        form_set_error('date_two_start' ,'Second request day too soon, please allow at least one business day in advance for the service request. If we are able to we will try to accomidate a more urgent matter to be adressed   sooner.');
    }
    if(request_too_soon($date_three_date)){
        form_set_error('date_three_start' ,'Third request day too soon, please allow at least one business day in advance for the service request. If we are able to we will try to accomidate a more urgent matter to be adressed   sooner.');
    }
    if(!sooner_than_three_months($date_one_date)){
        form_set_error('date_one_date', 'First service request day too far in advance, you can only request three months in advance');
    }
    if(!sooner_than_three_months($date_two_start, $date_two_end)){
        form_set_error('date_two_start date_two_end', 'Second service request day too far in advance, you can only request three months in advance');
    }
    if(!sooner_than_three_months($date_three_start, $date_three_end)){
        form_set_error('date_three_start date_three_end', 'Third service request day too far in advance, you can only request three months in advance');
    }
    if(all_days_are_the_same($date_one_date, $date_two_date, $date_three_date)){
        form_set_error('date_one_start date_one_end date_two_start date_two_end date_three_start date_three_end' , 'Only one request time allowed per day');
    }
    if(is_start_after_end($date_one_start, $date_one_end)){
        form_set_error('date_one_start _date_one_end', 'The end time for the first request date is before the start time.');
    }
    if(is_start_after_end($date_two_start, $date_two_end)){
        form_set_error('date_two_start date_two_end', 'The end time for the second request date is before the start time');
    }
    if(is_start_after_end($date_three_start, $date_three_end)){
        form_set_error('date_three_start date_three_end' ,'The end time for the third request date is before the start time');
    }
    if(start_too_early($date_one_start)){
        form_set_error('date_one_start', 'The start time for your first request is too early, please make it later than 9:00 AM.');
    }
    if(start_too_late($date_one_start)){
        form_set_error('date_one_start', 'The start time for your first request is too late, please make it earlier than 4:00 PM,');
    } 
    if(start_too_early($date_two_start)){
        form_set_error('date_two_start', 'The start time for your second request is too early, please make it later than 9:00 AM.');
    }
    if(start_too_late($date_two_start)){
        form_set_error('date_two_start', 'The start time for your second request is too late, please make it earlier than 4:00 PM,');
    }
    if(start_too_early($date_three_start)){
        form_set_error('date_three_start', 'The start time for your third request is too early, please make it later than 9:00 AM.');
    }
    if(start_too_late($date_three_start)){
        form_set_error('date_three_start', 'The start time for your third request is too late, please make it earlier than 4:00 PM,');
    }
    if(end_too_late($date_one_end)){
        form_set_error('date_one_end', 'The end time for your first request is too late, please make it earlier than 5:00 PM');
    }
    if(end_too_late($date_two_end)){
        form_set_error('date_two_end', 'The end time for your second request is too late, please make it earlier than 5:00 PM');
    }
    if(end_too_late($date_three_end)){
        form_set_error('date_three_end', 'The end time for your third request is too late, please make it earlier than 5:00 PM');
    }
    if(!enough_time($date_one_start, $date_one_end)){
        form_set_error('date_one_start date_one_end', 'We require a time window of at least 1 hour for each request time');
    }
    if(!enough_time($date_two_start, $date_two_end)){
        form_set_error('date_two_start date_two_end', 'We require a tiem window of at least 1 hour for each request time');
    }
    if(!enough_time($date_three_start, $date_three_end)){
        form_set_error('date_three_start date_three_end', 'We require a tiem window of at least 1 hour for each request time');
    }
    $machine_count = 0;
    $machine_count = count($machine_types);
    if($other_machine != ""){
        $machine_count++;
    }
    if($machine_count < 1){
        form_set_error('machine_types other_machine', 'Please provide a machine type');
    }
    $problem_count = 0;
    $problem_count = count($problem_types);
    $problem_count += count($problem_other);
    if($problem_count == 0){
        form_set_error('problem_types problem_other', 'Please provide a problem type');
    }
}
$business_contact;
function oss_client_oss_general_request_form_mail($key, &$message, $params){
    global $business_contact;
    $headers = array(
        'MIME-Version' => '1.0',
        'Content-Type' => 'text/html; charset=UTF-8;',
        'Content-Transfer-Encoding' => '8Bit',
        'X-Mailer' => 'Drupal',
        'CC' => $business_contact['email'],
    );
    foreach($headers as $key => $value){
        $message['headers'][$key] = $value;
    }
    $message['subject'] = $params['subject'];
    $message['body'] = $params['body'];
}
function getstaffInfo($email){
    $query = db_select('oss_client_staff', 'data')
        ->fields('data')
        ->condition('email', $email,'=')
        ->execute()
        ->fetchAssoc();
    return $query;
}
function oss_client_oss_general_request_form_submit($form, &$form_state){ 
    $clientData = getStaffInfo($_SESSION['shib_auth_username'].'@uic.edu');
    $req_name = $clientData['name'];
    $req_email = $clientData['email'];
    $department_selection = (int)$clientData['dptid'];
    $department;
    $department_name;
    $reach;
    $reach_contact;
    $business;
    global $business_contact;
    $req_office  = $clientData['office'];
    $reqid = get_last_reqid();
    $reqid++;
    $is_other_machine = $form_state['values']['other_machine'];
    switch($department_selection){
    case 1:
        $department = 1;
        $department_name = 'AACC';
        $reach = 1;
        $reach_contact = get_contact('oss_reach', 1);
        $business = 1;
        $business_contact = get_contact('oss_business', 1);
        break;
    case 0:
        $department = 0;
        $department_name = 'OVCA';
        $reach = 0;
        $reach_contact = get_contact('oss_reach', 0);
        $business = 0;
        $business_contact = get_contact('oss_business', 0);
        break;
    case 6:
        $department = 6;
        $department_name = 'OAE';
        $reach = 6;
        $reach_contact = get_contact('oss_reach', 6);
        $business = 6;
        $business_contact = get_contact('oss_business', 6);
        break;
    default:
        $department = -1;
        $department_name = 'other';
        $reach = array(
            ['name'] => '-1',
            ['email'] => '',
            ['phone'] => '0-0000',
            ['office'] => 'asdf',
        );
        $reach_contact = 'other';
        $business = $reach;
        $business_contact = $reach_contact;
    }
    $request = db_insert('oss_request')
        ->fields(array('reqid', 'name', 'email', 'phone', 'dptid', 'office', ))
        ->values(array(
            'reqid' => $reqid,
            'name' => $req_name,
            'email' => $req_email,
            'phone' => $clientData['phone'],
            'dptid' => $department,
            'office' => $clientData['office'],
        ))
        ->execute();
    $dates = array(
        $form_state['values']['date1_date'],
        $form_state['values']['date1_start'],
        $form_state['values']['date1_end'],
        $form_state['values']['date2_date'],
        $form_state['values']['date2_start'],
        $form_state['values']['date2_end'],
        $form_state['values']['date3_date'],
        $form_state['values']['date3_start'],
        $form_state['values']['date3_end'],
    );
    foreach($dates as $date){
        insert_date($reqid, $date);
    }
    $machine_value = array();
    $machine_types = array(
        0 => array('machine_wlaptop', 'Windows Laptop'),
        1 => array('machine_wdesktop', 'Windows Desktop'),
        2 => array('machine_alaptop', 'Apple Laptop'),
        3 => array('machine_adesktop', 'Apple Desktop'),
        4 => array('machine_tablet', 'Tablet'),
        5 => array('machine_printer', 'Printer'),
    );
    $mCount = 0;
    $hardware_types = array(
        10 => array('hardware_drive', 'Hard Drive'),
        11 => array('hardware_video', 'Video Display'),
        12 => array('hardware_peripherals', 'Peripherals'),
    );
    $internet_types = array(
        20 => array('internet_connection', 'Connecctivity issues'),
    );
    $migration_types = array(
        30 => array('migration_account', 'Account Migration'),
        31 => array('migration_data', 'Data Migration'),
        32 => array('migration_office', 'Office/Locarion Migration'),
    );
    $new_types = array(
        90 => array('new_computer', 'Computer set-up'),
        91 => array('new_image', 'Re-image'),
        92 => array('new_upgrade', 'Upgrade'),
    );
    $printer_types = array(
        50 => array('printer_connection', 'Printer Connectivity'),
        51 => array('printer_jams', 'Printer Jam'),
    );
    $recovery_types = array(
        80 => array('recovery_password', 'Password Recovery'),
        81 => array('recovery_data', 'Data Recovery'),
        82 => array('recovery_bit', 'Bit Locker Recovery'),
    );
    $software_types = array(
        60 => array('software_install', 'Install Software'),
        61 => array('software_microsoft', 'Microsoft Office'),
        //62 => array('software_pinnacle', 'Pinnacle'),
        63 => array('software_web', 'Web Browser'),
    );
    $qCount = 0;
    $other_questions = array();
    $other_types = array(
        13 => 'other_hardware',
        21 => 'other_internet',
        40 => 'nas_other',
        52 => 'other_printer',
        64 => 'other_software',
        70 => 'other_problem',
        71 => 'extra_info',
    );
    $oCount = 0;
    $answers = array();
    $problem_value = array();
    add_to_arrays(array_filter($form_state['values']['machine_types']), $machine_types, $machine_value, $reqid, $mCount);
    if($is_other_machine != ""){
        $machines[$mCount] = 6;
        $machine_value[$mCount] = $is_other_machine;
        insert_question_answer($reqid, $machines[$mCount], $machine_value[$mCount]);
        $mCount++;
    }
    $overall = array(array('hardware_types', $hardware_types,), array('internet_types', $internet_types,), array('migration_types', $migration_types,), array('new_user_computer_types',  $new_types,), array('printer_types', $printer_types,), array('recovery_types', $recovery_types,), array('software_types', $software_types,),
    );
    for($i = 0; $i < 7; $i++){
        add_to_arrays(array_filter($form_state['values'][$overall[$i][0]]), $overall[$i][1], $problem_value, $reqid, $qCount);
    }
    foreach($other_types as $type){
        if($form_state['values'][$type] != ""){
            $answers[$oCount] = $form_state['values'][$type];
            $problem_value[$qCount + $oCount] = $answers[$oCount];
            insert_question_answer($reqid, array_search($type, $other_types), $answers[$oCount]);
            $oCount++;
        }
    }
    $from = $req_email;
    $body[] = 'Thank you for submitting a request for On-Site Support. An ACCC member will follow up with you soon.<br/><br/>Here are the details of your request:<br/><br/>Requestors Information:'.
        '<br/>Name: '.$req_name.
        '<br/>Email: '.$req_email.
        '<br/>Phone: '.$clientData['phone'].
        '<br/>Department: '.$department_name.
        '<br/>Office Location: '.$req_office.
        '<br/><br/><br/>Request times:'.
        '<br/>Option 1 Date: '.$dates[0].
        '<br/>Option 1 Start Time: '.$dates[1].
        '<br/>Option 1 End TIme: '.$dates[2].
        '<br/>Option 2 Date: '.$dates[3].
        '<br/>Option 2 Start Time: '.$dates[4].
        '<br/>Option 2 End TIme: '.$dates[5].
        '<br/>Option 3 Date: '.$dates[6].
        '<br/>Option 3 Start Time: '.$dates[7].
        '<br/>Option 3 End Time: '.$dates[8].
        '<br/><br/><br/>Machine Type(s):';
    foreach($machine_value as $machine){
        $body[] .= '<br/>- '.$machine;
    }
    $body[] .= '<br/><br/>Problem(s)/Request(s)';
    foreach($problem_value as $problem){
        $body[] .= '<br/>- '.$problem;
    }
    $to = 'ovca-it@uic.edu';
    $params = array(
        'body' => $body,
        'subject' => $department_name.': On-Site Support Request for '.$req_name.' in '.$clientData['office'],
    );
    if(drupal_mail('oss_client_oss_general_request_form', $form_state['values']['form_build_id'], $to, language_default(), $params, $from, TRUE)){
        drupal_set_message('Thank you for your request. We will respond to your request within the next four hours.');
    } else {
        drupal_set_message('We had an error processing your request please try again in a few minutes');
    }
}

