<?php
/**
 *Implements page callback function - school_registeration_form
 */
function school_registeration_form($form, &$form_state){
//	$form['md-ta'] = array(
//		'#type' => 'markup',
//		'#markup' => '
//		    <div class="row">
//        <div class="input-field col s6">
//          <input placeholder="Placeholder" id="first_name" type="text" class="validate">
//          <label for="first_name">First Name</label>
//        </div>
//        <div class="input-field col s6">
//          <input id="last_name" type="text" class="validate">
//          <label for="last_name">Last Name</label>
//        </div>
//      </div>',
//	);
//	
	$form['lm'] = array(
		'#type' => 'textfield',
		'#title' => 'Last Name',
		'#prefix' => '<div class = "input-field col s12">',
		'#suffix' => '</div>',
		'#size' => 10
	);
	dsm(drupal_get_path('theme', 'bootstrap_material').'/images/user.jpg');
	$form['ta'] = array(
		'#type' => 'textarea',
		'#title' => 'Textarea',
		'#attributes' => array('class' => array('materialize-textarea'),'id' => array('edit-ta')),
		'#prefix' => '<div class="row"><div class = "input-field col s12">',
		'#suffix' => '</div></div>',
		'#resizable' => FALSE,
	);
	
	$form['ss'] = array(
		'#type' => 'fieldset',
	);
	
	$form['ss']['nameofschool'] = array(
		'#title' => t('Name of School'),
		'#type' => 'textfield',
		'#prefix' => '<div class = "input-field col s12">',
		'#suffix' => '</div>',
	);
	
	$form['ss']['slogan'] = array(
		'#type' => 'textfield',
		'#title' => t('Slogan of the School'),
		'#default_value' => isset($slogan)? $slogan: NULL,
		'#prefix' => '<div class = "input-field col s12">',
		'#suffix' => '</div>',
	);
	
	$form['ss']['board'] = array(
		'#type' => 'select',
		'#title' => t('Board'),
		'#options' => drupal_map_assoc(array(
			t('C.B.S.E.'), t('I.C.S.E.'), t('State Board'), t('Other')
		)),
		'#attributes' => array('class' => array('gradingselectfield')),
		'#prefix' => '<div class = "input-field col s12">',
		'#suffix' => '</div>',
		'#default_value' => isset($board)? $board: NULL,
	);
	
	$form['ss']['other'] = array(
		'#type' => 'container',
		'#states' => array(
			'visible' => array(
			  ':input[name = "board"]' => array('value' => 'Other'),
			),
		),
	);
	
	$form['ss']['other']['desc'] = array(
		'#type' => 'textfield',
		'#title' => 'Description',
		'#prefix' => '<div class = "input-field col s12">',
		'#suffix' => '</div>',
	);
	
	$form['ss']['sb'] = array(
		'#type' => 'container',
		'#states' => array(
			'visible' => array(
			  ':input[name = "board"]' => array('value' => 'State Board'),
			),
		),
	);
  
  $states = array('Andhra Pradesh', 'Arunachal Pradesh', 'Assam', 'Bihar', 'Chhattisgarh', 'Goa', 'Gujarat', 'Haryana', 'Himachal Pradesh', 'Jammu and Kashmir',
  'Jharkhand', 'Karnataka', 'Kerala', 'Madhya Pradesh', 'Maharashtra', 'Manipur', 'Meghalaya', 'Mizoram', 'Nagaland', 'Odisha(Orissa)', 'Punjab',
  'Rajasthan', 'Sikkim', 'Tamil Nadu', 'Tripura', 'Uttar Pradesh', 'Uttarakhand', 'West Bengal');
  
  $form['ss']['sb']['sas'] = array(
    '#type' => 'select',
    '#title' => 'Select A State',
    '#options' => drupal_map_assoc($states),
    
  );
	
	$form['ss']['school_code'] = array(
		'#title' => t('School Code'),
		'#type' => 'textfield',
		
		'#default_value' => isset($school_code)? $school_code: NULL,
	);
	
	$form['ss']['affiliation_no'] = array(
		'#title' => t('Affiliation No.'),
		'#type' => 'textfield',
		
		'#default_value' => isset($affiliation_no)? $affiliation_no: NULL,
	);
	
	$form['ss']['establishment_year'] = array(
		'#type' => 'textfield',
		'#title' => t('Year of Establishment'),
		
		'#default_value' => isset($establishment_year)? $establishment_year: NULL,
	);
	
	$form['ss']['hostel'] = array(
		'#type' => 'radios',
		'#title' => t('Hostel Facility'),
		'#options' => drupal_map_assoc(array('YES', 'NO')),
		'#default_value' => isset($hostel)? $hostel: NULL,
	);
	
	$form['ss']['transport'] = array(
		'#type' => 'radios',
		'#title' => t('Transport Facility'),
		'#options' => drupal_map_assoc(array('YES', 'NO')),
		'#default_value' => isset($transport)? $transport: NULL,
	);
	
	$form['ss']['hs'] = array(
		'#type' => 'fieldset',
		'#title' => 'Name of Houses',
	);
	
	$form['ss']['hs']['house1'] = array(
		'#type' => 'textfield',
		'#size' => 10,
		'#attributes' => array('placeholder' => 'House 1'),
		'#default_value' => isset($house1)? $house1: NULL,
	);
	
	$form['ss']['hs']['house2'] = array(
		'#type' => 'textfield',
		'#size' => 10,
		'#attributes' => array('placeholder' => 'House 2'),
		'#default_value' => isset($house2)? $house2: NULL,
	);
	
	$form['ss']['hs']['house3'] = array(
		'#type' => 'textfield',
		'#size' => 10,
		'#attributes' => array('placeholder' => 'House 3'),
		'#default_value' => isset($house3)? $house3: NULL,
	);
	
	$form['ss']['hs']['house4'] = array(
		'#type' => 'textfield',
		'#size' => 10,
		'#attributes' => array('placeholder' => 'House 4'),
		'#default_value' => isset($house4)? $house4: NULL,
	);
	
	$form['ss']['ci'] = array(
		'#type' => 'fieldset',
		'#title' => 'Contact Information',
	);
	
	$form['ss']['ci']['contactofschool'] = array(
		'#title' => t('Contact Number'),
		'#type' => 'textfield',
			  
		'#rules' => array(
			'numeric',
			'length[10,15]',
			),
		'#default_value' => isset($contact)? $contact: NULL,
	);
	
	$form['ss']['ci']['website'] = array(
		'#type' => 'textfield',
		'#title' => t('Official website'),
		'#rules' => array('email'),
		'#default_value' => isset($website)? $website: NULL,
	);
	
	$form['ss']['ci']['email'] = array(
		'#type' => 'textfield',
		'#title' => t('Official e-mail ID'),
		'#rules' => array('email'),
		'#default_value' => isset($email)? $email: NULL,
	);
	
	$form['ss']['ci']['fax'] = array(
		'#title' => t('FAX no.'),
		'#type' => 'textfield',
		'#rules' => array(
			'numeric',
			'length[10,15]',
		),
		'#default_value' => isset($fax)? $fax: NULL,
	);
	
	$form['ss']['ci']['ad'] = array(
		'#type' => 'fieldset',
		'#title' => t('Address'),
	);
	
	$form['ss']['ci']['ad']['line1'] = array(
		'#type' => 'textfield',
		'#title' => t('Line 1'),
		'#size' => 100,
		'#default_value' => isset($line1)? $line1: NULL,
	);
	
	$form['ss']['ci']['ad']['line2'] = array(
		'#type' => 'textfield',
		'#title' => t('Line 2'),
		'#size' => 100,
		'#default_value' => isset($line2)? $line2: NULL,
	);
	
	$form['ss']['ci']['ad']['City'] = array(
		'#type' => 'textfield',
		'#title' => t('City'),
		'#size' => 30,
		'#default_value' => isset($city)? $city: NULL,
	);
	
	$form['ss']['ci']['ad']['State'] = array(
		'#type' => 'textfield',
		'#title' => t('State'),
		'#size' => 30,
		'#default_value' => isset($state)? $state: NULL,
	);
	
	$form['ss']['ci']['ad']['pin'] = array(
		'#type' => 'textfield',
		'#title' => t('Pin Code'),
		'#size' => 10,
		'#default_value' => isset($pin)? $pin: NULL,
	);
	
	$form['ss']['ci']['ad']['country'] = array(
		'#type' => 'textfield',
		'#title' => t('Country'),
		'#size' => 30,
		'#default_value' => isset($country)? $country: NULL,
	);
	
	$form['ss']['general_setting'] = array(
		'#type' => 'fieldset',
		'#title' => 'General Settings',
	);
	
	$form['ss']['general_setting']['financialyear'] = array(
		'#title' => t('Financial Year'),
		'#type' => 'fieldset',
	);  
		
	$form['ss']['general_setting']['financialyear']['financialyearstart'] = array(
		'#type' => 'date_popup',
		'#title' => t('Start Date'),
		'#date_format' => 'd/m/Y',
		
		'#attributes' => array('placeholder' => 'From'),
		'#default_value' => isset($financialyearstart)? $financialyearstart: NULL,
		);
		
	$form['ss']['general_setting']['financialyear']['financialyearend'] = array(
		'#type' => 'date_popup',
		'#title' => t('End Date'),
		'#date_format' => 'd/m/Y',
		
		'#attributes' => array('placeholder' => 'To'),
		'#default_value' => isset($financialyearend)? $financialyearend: NULL,
	);
	
	$form['ss']['general_setting']['academicyear'] = array(
		'#title' => t('Academic Year'),
		'#type' => 'fieldset',
		
	);  
	
	$form['ss']['general_setting']['academicyear']['academicyearstart'] = array(
		'#type' => 'date_popup',
		'#title' => t('Start Date'),
		'#date_format' => 'd/m/Y',
		
		'#attributes' => array('placeholder' => 'From'),
		'#default_value' => isset($academicyearstart)? $academicyearstart: NULL,
	);
	
	
	$form['ss']['general_setting']['academicyear']['academicyearend'] = array(
		'#type' => 'date_popup',
		'#title' => t('End Date'),
		'#date_format' => 'd/m/Y',
		
		'#attributes' => array('placeholder' => 'To'),
		'#default_value' => isset($academicyearend)? $academicyearend: NULL,
	);
	
	$form['ss']['general_setting']['notice_period']= array(
		'#type' => 'select',
		'#title' => 'Notice period for staff resingnation',
		'#options' => drupal_map_assoc(array('--Select--','7 days', '15 days', '1 Month', '2 Months')),
		
		'#default_value' => isset($notice_period)? $notice_period: NULL,
	);
	
	$form['ss']['submit'] = array(
		'#type' => 'submit',
		'#value' => 'Save',
		'#submit' => array('basicinfo_form_submit'),
	);
	//$options = array();
	//$options = array('--Select--','7 days', '15 days', '1 Month', '2 Months');
	return $form;
}

function basicinfo_form_submit($form, &$form_state){
	dsm($form_state);
}

/**
* Altering Date Popup to remove labels and description for specific field
*/
function school_registeration_date_popup_process_alter(&$element, &$form_state, $context) {
  unset($element['date']['#description']);
  unset($element['date']['#title']);
	unset($element['time']['#title']);
	unset($element['time']['#description']);
  return $element;   
}
