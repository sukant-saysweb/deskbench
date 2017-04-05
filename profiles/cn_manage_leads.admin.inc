<?php
/**
 *Implements page callback functio - cn_manage_leads
 */
function cn_manage_leads($form, &$form_state, $tn_no){
	$lds = db_query("
		SELECT * from field_data_field_transaction_no_ where field_transaction_no__value = :tn;", array(':tn' => $tn_no)
	);
	foreach($lds as $ld){
		$lead_no = $ld->entity_id;
	}
	$leads = node_load($lead_no);
	$lead_node = node_load($lead_no);
	$current_path = current_path();
	global $user;
	$check_in = date('d-m-Y',strtotime($leads->field_leads_check_in_date['und'][0]['value']));
	$check_out = date('d-m-Y',strtotime($leads->field_leads_check_out_date['und'][0]['value']));
	$nights = (strtotime($check_out) - strtotime($check_in)) / 86400;

	$guest_name = '<ul>';
	foreach($leads->field_leads_guest_names['und'] as $arr){
		$guest_name .= '<li>'.$arr['value'].'</h6>';
	}
	$guest_name .= '<ul>';

	$terms =taxonomy_term_load($leads->field_leads_status['und']['0']['tid']);
	$status = $terms->name;
	global $base_url;
	$edit_path = $base_url.'/admin/manage_leads/'.$tn_no.'#overlay=admin/manage_leads/'.$tn_no.'/edit-lead';
	$delete_path = $base_url.'/node/'.$lead_no.'/delete';
	$path = $base_url.'/ajax_link_callback/nojs/';
	$ajax_path = $base_url."/ajax_search_hotel/".$lead_node->field_transaction_no_['und'][0]['value'];

	$row[$leads->field_transaction_no_['und'][0]['value']] = array(
		'#tree' =>TRUE,
		$leads->field_transaction_no_['und'][0]['value'] => array(  //Generating unique array id for every form element
			'c1' =>array(
				'#type' => 'markup',
				'#markup' => '<h4 style = "text-align: left !important;">'. $leads->field_transaction_no_['und'][0]['value'] .'</h4>',
			),
			'c2' =>array(
				'#type' => 'markup',
				'#markup' => '<h4 style = "text-align: left !important;">'. $check_in .'</h4>',
			),
			'c3' =>array(
				'#type' => 'markup',
				'#markup' => '<h4 style = "text-align: left !important;">'. $check_out .'</h4>',
			),
			'c4' =>array(
				'#type' => 'markup',
				'#markup' => '<h4 style = "text-align: left !important;">'. $nights .'</h4>',
			),
			'c5' =>array(
				'#type' => 'markup',
				'#markup' => '<h4 style = "text-align: left !important;">'. $leads->field_leads_country['und'][0]['value'].','.$leads->field_leads_city['und'][0]['value'] .'</h4>',
			),
			'c6' =>array(
				'#type' => 'markup',
				'#markup' => $guest_name,
			),
			'c7' =>array(
				'#type' => 'markup',
				'#markup' => '<h4 style = "text-align: left !important;">'. $leads->field_no_of_adults['und'][0]['value'] .'</h4>',
			),
			'c8' =>array(
				'#type' => 'markup',
				'#markup' => '<h4 style = "text-align: left !important;">'. $leads->field_leads_number_of_children['und'][0]['value'] .'</h4>',
			),
			'c9' =>array(
				'#type' => 'markup',
				'#markup' => '<h4 style = "text-align: left !important;">'. $leads->field_leads_number_of_infants['und'][0]['value'] .'</h4>',
			),
			'c10' =>array(
				'#type' => 'markup',
				'#markup' => '<h4 style = "text-align: left !important;">'. $status .'</h4>',
			),
			'c11' =>array(
				'#type' => 'markup',
				'#markup' => '<h4 style = "text-align: left !important;">
				<a href = "'.$edit_path.'"/edit"><i class="fa fa-pencil" aria-hidden="true" style = "font-size: 35px !important;"></i></a>&nbsp;&nbsp;
				<a href = "'.$delete_path.'"><i class="fa fa-trash" aria-hidden="true" style = "font-size: 35px !important;"></i></a>&nbsp;&nbsp;
				<a class="ajax-link" href = "'.$ajax_path.'" rel="#ajax-target"><i class="fa fa-search" aria-hidden="true" style = "font-size: 35px !important;"></i></a>&nbsp;&nbsp;
				</h4>',
			),
		),
	);

	$redirect_path = base_path().'view_options_form/'.$lead_node->field_transaction_no_['und'][0]['value'];
	$form['hsr']['link'] = array(
		'#type' => 'markup',
		'#markup' => '<a id = "yourLinkID" class="colorbox-node" style = "display: none;" href="'.$redirect_path.'" data-inner-width="80%" data-inner-height="800">Test</a>',
	);

	$form['tab'] = array(
		'#theme' => 'leads_table',
		'rows' => $row,
	);

	$form['#attached']['js'][] = array(
    'type' => 'file',
    'data' => drupal_get_path('module', 'leads') . '/leads.js',
  );

	$form['ajax'] = array(
		'#type' => 'markup',
		'#markup' => '<div id="ajax-target"></div>',
	);
	//$output = drupal_get_form('hotel_search');
	return $form;
}


/**
 *Ajax function to deliver hotel search
 */
function ajax_search_hotel($form, &$form_state, $tn_no){
	$lds = db_query("
		SELECT * from field_data_field_transaction_no_ where field_transaction_no__value = :tn;", array(':tn' => $tn_no)
	);
	foreach($lds as $ld){
		$lead_no = $ld->entity_id;
	}
	$form['vof1'] = array(
		'#type' => 'submit',
		'#value' => 'View Options Form',
	);

	$form['save1'] = array(
		'#type' => 'submit',
		'#value' => 'Save Options',
	);

	$form['hsr'] = array(
		'#type' => 'fieldset',
		'#title' => 'Hotel Search Results',
		'#collapsible' => TRUE,
		'#collapsed' => FALSE,
	);

	$form['#attached']['js'][] = array(
    'type' => 'file',
    'data' => drupal_get_path('module', 'leads') . '/leads.js',
  );

	$form['lead'] = array(
		'#type' => 'value',
		'#value' => $lead_no
	);

	$data = $hsr_row = array();
	$path = drupal_get_path('module', 'leads').'/leads.js';
	drupal_add_js($path);
	if(isset($form_state['values'])){
		global $user;
		$currency_tid = $net_rate = $rate_slab_name = $net_rate_include_tax =  NULL;
		$master = $rate_slab_options = $sel_hotels =array();

		$leads = node_load($lead_no);
		$hotels = db_query("
			SELECT * from field_data_field_hotel_city_id where field_hotel_city_id_value = :ci;", array(':ci' => $leads->field_leads_city_id['und'][0]['value'])
		);
		foreach($hotels as $hotel){
			$hotel_rooms = db_query("
				SELECT * from field_data_field_hotel_name_rooms where field_hotel_name_rooms_target_id = :ti;",
				array(':ti' => $hotel->entity_id)
			);

			foreach($hotel_rooms as $hr){
				$hr_node = node_load($hr->entity_id);
				$master[$hr_node->nid] = $hotel->entity_id;
				$sel_hotels[$hr_node->entity_id] = $hotel->entity_id;
			}
		}

		if($form_state['values']['hotel_filter'] != '0'){
			foreach($master as $hr => $hotel){
				if($hotel == $form_state['values']['hotel_filter']){
					$filter_hotel[$hr] = $hotel;
				}
			}
			$master = array_intersect($master, $filter_hotel);
		}

		if($form_state['values']['room_filter'] != NULL){
			foreach($master as $hr => $hotel){
				foreach($form_state['values']['room_filter'] as $rf){
					$hr_node = node_load($hr);
					if($hr_node->field_hotel_room_type['und']['0']['tid'] == $rf){
						$room_filter[$hr] = $hotel;
					}
				}
			}
			$master = array_intersect_assoc($master, $room_filter);
		}

		if($form_state['values']['scr_filter'] != NULL){
			foreach($master as $hr => $hotel){
				$hr_node = node_load($hr);
				if($hr_node->field_special_contract_rate_value['und'][0]['value'] == $form_state['values']['scr_filter']){
					$scr_filter[$hr] = $hotel;
				}
			}
			$master = array_intersect_assoc($master, $scr_filter);
		}

		/*
		if($form_state['values']['room_filter'] != NULL){
			foreach($sel_hotels as $hotel){
				foreach($form_state['values']['room_filter'] as $rt){
					$these_hotel_rooms = db_query("
						SELECT * from field_data_field_hotel_room_type where field_hotel_room_type_tid = :ti;",
						array(':ti' => $rt)
					);
					foreach($these_hotel_rooms as $thr){
						$these_hotels = db_query("
							SELECT * from field_data_field_hotel_name_rooms where entity_id = :ti;",
							array(':ti' => $thr->entity_id)
						);
						foreach($these_hotels as $th){
							$filter_rooms[$th->field_hotel_name_rooms_target_id] = $th->field_hotel_name_rooms_target_id;
						}
					}
					$master = array_intersect($master, $filter_rooms);
				}
			}
		}
		*/

		foreach($master as $hr_nid => $hotel){
			$hotel_node = node_load($hotel);
			$hotel_options[$hotel] = $hotel_node->title;
			$amenities_list = NULL;
			$count = 0;

			if(isset($hotel_node->field_hotel_amenities['und'])){
				foreach($hotel_node->field_hotel_amenities['und'] as $amenities){
					$amenities_list .= taxonomy_term_load($amenities['tid'])->name.', ';
				}
			}

			$vocabulary = taxonomy_vocabulary_machine_name_load('currencies');
			$payment_policies = array('- Select -');
			$vocabulary = taxonomy_vocabulary_machine_name_load('payment_policies');
			$terms = entity_load('taxonomy_term', FALSE, array('vid' => $vocabulary->vid));
			foreach($terms as $term){
				$payment_policies[$term->tid] = $term->name;
			}

			$hr_node = node_load($hr_nid);
			$standard_rates = db_query("
				SELECT * from field_data_field_hotel_name_sr where field_hotel_name_sr_target_id = :ti;",
				array(':ti' => $hotel)
			);
			foreach($standard_rates as $sr){
				$sr_node = node_load($sr->entity_id);
				if($sr_node->field_hotel_room_type['und']['0']['tid'] == $hr_node->field_hotel_room_type['und']['0']['tid']){
					$rate_slab = $sr_node->field_hotel_rate_slab['und']['0']['tid'];
					$currency_tid = $sr_node->field_sr_currency['und']['0']['tid'];
					$net_rate = $sr_node->field_net_rate['und'][0]['value'];
					$net_rate_include_tax = $sr_node->field_does_net_rate_include_tax_['und'][0]['value'];
					$rate_slab_name = taxonomy_term_load($rate_slab)->name;
				}else{
					$rate_slab = NULL;
					$currency_tid = NULL;
					$net_rate = NULL;
					$net_rate_include_tax = NULL;
					$rate_slab_name = NULL;
				}
			}

			if(isset($hr_node->field_hotel_room_type['und']['0']['tid'])){
				$room_type = taxonomy_term_load($hr_node->field_hotel_room_type['und']['0']['tid'])->name;
				$room_type_options[$hr_node->field_hotel_room_type['und']['0']['tid']] = taxonomy_term_load($hr_node->field_hotel_room_type['und']['0']['tid'])->name;
			}

			$bedding = taxonomy_term_load($hr_node->field_bedding['und']['0']['tid'])->name;

			if($hr_node->field_special_contract_rate['und'][0]['value'] == 0){
				$scr = 'No';
			}else{
				$scr = 'Yes';
			}
			if(isset($room_type) && $room_type != NULL){
				if($form_state['values']['rs_filter'] != NULL){
					foreach($form_state['values']['rs_filter'] as $scrf){
						if($scrf == $rate_slab){
							$data[$hr_node->nid]['name'] = $hotel_node->title;
							$data[$hr_node->nid]['room_type'] = $room_type;
							$data[$hr_node->nid]['bedding'] = $bedding;
							$data[$hr_node->nid]['field_max_occupancy'] = $hr_node->field_max_occupancy['und'][0]['value'];
							$data[$hr_node->nid]['scr'] = $scr;
							$data[$hr_node->nid]['rate_slab_name'] = $rate_slab_name;
							$data[$hr_node->nid]['internet'] = $hr_node->field_internet_included['und'][0]['value'];
							$data[$hr_node->nid]['breakfast'] = $hr_node->field_breakfast_included['und'][0]['value'];
							$data[$hr_node->nid]['city'] = $hotel_node->field_hotel_city['und'][0]['value'];
							$data[$hr_node->nid]['currency'] = $currency_tid;
							$data[$hr_node->nid]['net_rate'] = $net_rate;
							$data[$hr_node->nid]['tax'] = $net_rate_include_tax;
							$data[$hr_node->nid]['cancel'] = $hotel_node->field_cancellation_policy['und'][0]['value'];
							$data[$hr_node->nid]['pp'] = $payment_policies;
							$data[$hr_node->nid]['amenities'] = $amenities_list;
						}
					}
				}else{
					$data[$hr_node->nid]['name'] = $hotel_node->title;
					$data[$hr_node->nid]['room_type'] = $room_type;
					$data[$hr_node->nid]['bedding'] = $bedding;
					$data[$hr_node->nid]['field_max_occupancy'] = $hr_node->field_max_occupancy['und'][0]['value'];
					$data[$hr_node->nid]['scr'] = $scr;
					$data[$hr_node->nid]['rate_slab_name'] = $rate_slab_name;
					$data[$hr_node->nid]['internet'] = $hr_node->field_internet_included['und'][0]['value'];
					$data[$hr_node->nid]['breakfast'] = $hr_node->field_breakfast_included['und'][0]['value'];
					$data[$hr_node->nid]['city'] = $hotel_node->field_hotel_city['und'][0]['value'];
					$data[$hr_node->nid]['currency'] = $currency_tid;
					$data[$hr_node->nid]['net_rate'] = $net_rate;
					$data[$hr_node->nid]['tax'] = $net_rate_include_tax;
					$data[$hr_node->nid]['cancel'] = $hotel_node->field_cancellation_policy['und'][0]['value'];
					$data[$hr_node->nid]['pp'] = $payment_policies;
					$data[$hr_node->nid]['amenities'] = $amenities_list;
				}
			}
		}
	}else{
		global $user;
		$leads = node_load($lead_no);
		$currency_tid = NULL;
		$hotel_options = array('Select a Property');
		$room_type_options = array();
		$rate_slab_options = array();

		$hotels = db_query("
			SELECT * from field_data_field_hotel_city_id where field_hotel_city_id_value = :ci;", array(':ci' => $leads->field_leads_city_id['und'][0]['value'])
		);
		foreach($hotels as $hotel){
			$hotel_node = node_load($hotel->entity_id);
			$hotel_options[$hotel->entity_id] = $hotel_node->title;
			$amenities_list = NULL;
			$count = 0;

			if(isset($hotel_node->field_hotel_amenities['und'])){
				foreach($hotel_node->field_hotel_amenities['und'] as $amenities){
					$amenities_list .= taxonomy_term_load($amenities['tid'])->name.', ';
				}
			}

			$payment_policies = array('- Select -');
			$vocabulary = taxonomy_vocabulary_machine_name_load('payment_policies');
			$terms = entity_load('taxonomy_term', FALSE, array('vid' => $vocabulary->vid));
			foreach($terms as $term){
				$payment_policies[$term->tid] = $term->name;
			}

			$hotel_rooms = db_query("
				SELECT * from field_data_field_hotel_name_rooms where field_hotel_name_rooms_target_id = :ti;",
				array(':ti' => $hotel_node->nid)
			);

			foreach($hotel_rooms as $hr){
				$hr_node = node_load($hr->entity_id);

				$standard_rates = db_query("
					SELECT * from field_data_field_hotel_name_sr where field_hotel_name_sr_target_id = :ti;",
					array(':ti' => $hotel->entity_id)
				);
				foreach($standard_rates as $sr){
					$sr_node = node_load($sr->entity_id);
					if(isset($sr_node->field_hotel_room_type['und']['0']['tid']) && isset($hr_node->field_hotel_room_type['und']['0']['tid'])){
						if($sr_node->field_hotel_room_type['und']['0']['tid'] == $hr_node->field_hotel_room_type['und']['0']['tid']){
							$rate_slab = $sr_node->field_hotel_rate_slab['und']['0']['tid'];
							$currency_tid = $sr_node->field_sr_currency['und']['0']['tid'];
							$net_rate = $sr_node->field_net_rate['und'][0]['value'];
							$net_rate_include_tax = $sr_node->field_does_net_rate_include_tax_['und'][0]['value'];
							$rate_slab_name = taxonomy_term_load($rate_slab)->name;
						}else{
							$rate_slab = NULL;
							$currency_tid = NULL;
							$net_rate = NULL;
							$net_rate_include_tax = NULL;
							$rate_slab_name = NULL;
						}
					}
				}
				if($currency_tid != NULL){
					$currency = taxonomy_term_load($currency_tid)->name;
				}

				if(isset($hr_node->field_hotel_room_type['und']['0']['tid'])){
					$room_type = taxonomy_term_load($hr_node->field_hotel_room_type['und']['0']['tid'])->name;
					$room_type_options[$hr_node->field_hotel_room_type['und']['0']['tid']] = taxonomy_term_load($hr_node->field_hotel_room_type['und']['0']['tid'])->name;
				}

				$bedding = taxonomy_term_load($hr_node->field_bedding['und']['0']['tid'])->name;

				if($hr_node->field_special_contract_rate['und'][0]['value'] == 0){
					$scr = 'No';
				}else{
					$scr = 'Yes';
				}
				if(isset($room_type) && $room_type != NULL){
					$data[$hr_node->nid]['name'] = $hotel_node->title;
					$data[$hr_node->nid]['room_type'] = $room_type;
					$data[$hr_node->nid]['bedding'] = $bedding;
					$data[$hr_node->nid]['field_max_occupancy'] = $hr_node->field_max_occupancy['und'][0]['value'];
					$data[$hr_node->nid]['scr'] = $scr;
					$data[$hr_node->nid]['rate_slab_name'] = $rate_slab_name;
					$data[$hr_node->nid]['internet'] = $hr_node->field_internet_included['und'][0]['value'];
					$data[$hr_node->nid]['breakfast'] = $hr_node->field_breakfast_included['und'][0]['value'];
					$data[$hr_node->nid]['city'] = $hotel_node->field_hotel_city['und'][0]['value'];
					$data[$hr_node->nid]['currency'] = $currency_tid;
					$data[$hr_node->nid]['net_rate'] = $net_rate;
					$data[$hr_node->nid]['tax'] = $net_rate_include_tax;
					$data[$hr_node->nid]['cancel'] = $hotel_node->field_cancellation_policy['und'][0]['value'];
					$data[$hr_node->nid]['pp'] = $payment_policies;
					$data[$hr_node->nid]['amenities'] = $amenities_list;
				}
			}
		}
	}

	$form['hsr']['filter'] = array(
		'#type' => 'container',
		'#title' => 'Filter By - ',
	);

	$form['hsr']['filter']['hotel_filter'] = array(
		'#type' => 'select',
		'#options' => $hotel_options,
    '#title' => t('Property'),
		'#validated' => TRUE,
	);

	asort($room_type_options);
	$form['hsr']['filter']['room_filter'] = array(
		'#type' => 'select',
		'#options' => $room_type_options,
    '#title' => t('Room Type'),
		'#multiple' => TRUE,
		'#size' => 5,
		'#validated' => TRUE,
		'#chosen' => FALSE,
	);

	$vocabulary = taxonomy_vocabulary_machine_name_load('rate_slabs');
	$rate_slabs = db_query("
		SELECT * from taxonomy_term_data where vid = :vid;", array(':vid' => $vocabulary->vid)
	);
	foreach($rate_slabs as $rso){
		$rate_slab_options[$rso->tid] = $rso->name;
	}

	asort($rate_slab_options);
	$form['hsr']['filter']['rs_filter'] = array(
		'#type' => 'select',
		'#options' => $rate_slab_options,
    '#title' => t('Rate Slab'),
		'#multiple' => TRUE,
		'#size' => 5,
		'#validated' => TRUE,
		'#chosen' => FALSE,
	);

	$form['hsr']['filter']['scr_filter'] = array(
		'#type' => 'checkbox',
    '#title' => t('Special Contract Rate'),
		'#validated' => TRUE,
	);

	$form['hsr']['filter']['cancel'] = array(
		'#type' => 'button',
    '#value' => t('Search'),
		'#ajax' => array(
      'event' => 'click',
      'callback' => 'apply_filter_ajax',
      'wrapper' => 'filter_wrapper',
      'method' => 'replace',
      'effect' => 'slide',
    ),
		'#validated' => TRUE,
	);
	/*
	$form['hsr']['filter']['delete'] = array(
		'#type' => 'button',
    '#value' => t('Reset'),
		'#ajax' => array(
      'event' => 'click',
      'callback' => 'reset_filter_ajax',
      'wrapper' => 'filter_wrapper',
      'method' => 'replace',
      'effect' => 'slide',
    ),
		'#validated' => TRUE,
	);
	*/
	$vocabulary = taxonomy_vocabulary_machine_name_load('currencies');
	$get_currencies = db_query("
		SELECT * from taxonomy_term_data where vid = :vid;", array(':vid' => $vocabulary->vid)
	);
	foreach($get_currencies as $gc){
		$currencies[$gc->tid] = $gc->name;
	}

	foreach($data as $hotel_id => $array){
		$this_hotel = NULL;
		$options = db_query("
			SELECT * from field_data_field_options_room_type where field_options_room_type_target_id = :ld;",
			array(':ld' => $hotel_id)
		);
		foreach($options as $option){
			$options_node = node_load($option->entity_id);
			if($options_node->field_lead_options['und'][0]['target_id'] == $lead_no){
				$this_hotel = $options_node->field_options_room_type['und'][0]['target_id'];
			}
		}

		if($hotel_id == $this_hotel){
			//dsm($options_node);
			if($options_node->field_option_internet['und'][0]['value'] == 1){
				$internet = 'Yes';
			}else{
				$internet = 'No';
			}

			if($options_node->field_option_breakfast['und'][0]['value'] == 1){
				$breakfast = 'Yes';
			}else{
				$breakfast = 'No';
			}
			$hsr_row[$hotel_id] = array(
				'#tree' =>TRUE,
				$hotel_id => array(  //Generating unique array id for every form element
					'c1' =>array(
						'#type' => 'checkbox',
						'#default_value' => 1,
					),
					'c2' =>array(
						'#type' => 'markup',
						'#markup' => '<h4 style = "text-align: left !important;" class = "hotel_name">'. $array['name'] .'</h4>',
					),
					'c3' =>array(
						'#type' => 'markup',
						'#markup' => '<h4 style = "text-align: left !important;">'. $array['room_type'] .'</h4>',
					),
					'c4' =>array(
						'#type' => 'markup',
						'#markup' => '<h4 style = "text-align: left !important;">'. $array['bedding'] .'</h4>',
					),
					'c5' =>array(
						'#type' => 'markup',
						'#markup' => '<h4 style = "text-align: left !important;">'. $array['field_max_occupancy'] .'</h4>',
					),
					'c6' => array(
						'#type' => 'textfield',
						'#size' => 5,
						'#default_value' => $options_node->field_options_actual_occupancy['und'][0]['value'],
						'#required' => TRUE,
						//'#attached' => drupal_add_js('(function($){alert("wow");})(jQuery);','inline')
					),
					'c7' =>array(
						'#type' => 'markup',
						'#markup' => '<h4 style = "text-align: left !important;">'. $array['scr'] .'</h4>',
					),
					'c8' =>array(
						'#type' => 'markup',
						'#markup' => '<h4 style = "text-align: left !important;">'. $array['rate_slab_name'] .'</h4>',
					),
					'c9' => array(
						'#type' => 'select',
						'#options' => drupal_map_assoc(array('No', 'Yes')),
						'#default_value' => $internet,
						'#chosen' => FALSE,
					),
					'c10' => array(
						'#type' => 'textfield',
						'#size' => 5,
						'#default_value' => $options_node->field_option_internet_cost['und'][0]['value'],
					),
					'c11' => array(
						'#type' => 'select',
						'#options' => drupal_map_assoc(array('No', 'Yes')),
						'#default_value' => $breakfast,
						'#chosen' => FALSE,
					),
					'c12' => array(
						'#type' => 'textfield',
						'#size' => 5,
						'#default_value' => $options_node->field_option_breakfast_cost['und'][0]['value'],
					),
					'c13' => array(
						'#type' => 'markup',
						'#markup' => '<h4 style = "text-align: left !important;">'. $array['city'] .'</h4>',
					),
					'c14' => array(
						'#type' => 'select',
						'#options' => $currencies,
						'#default_value' => $options_node->field_option_currency['und'][0]['tid'],
						'#chosen' => FALSE,
						'#required' => TRUE,
					),
					'c15' => array(
						'#type' => 'textfield',
						'#default_value' => $options_node->field_option_rate['und'][0]['value'],
						'#size' => 5,
						'#required' => TRUE,
					),
					'c16' => array(
						'#type' => 'textfield',
						'#size' => 20,
						'#default_value' => $options_node->field_option_rate_source['und'][0]['value'],
						'#required' => TRUE,
					),
					'c17' => array(
						'#type' => 'checkbox',
						'#default_value' => $array['tax'],
						'#default_value' => $options_node->field_option_tax['und'][0]['value'],
					),
					'c18' => array(
						'#type' => 'textfield',
						'#default_value' => $options_node->field_option_cancel['und'][0]['value'],
						'#size' => 30,
					),
					'c19' => array(
						'#type' => 'select',
						'#options' => $array['pp'],
						'#default_value' => $options_node->field_options_payment_tid['und']['0']['tid'],
						'#chosen' => FALSE,
						'#required' => TRUE,
					),
					'c20' => array(
						'#type' => 'textfield',
						'#size' => 20,
						'#default_value' => $options_node->field_option_distance['und'][0]['value'],
					),
					'c21' => array(
						'#type' => 'textfield',
						'#default_value' => $options_node->field_option_amenities['und'][0]['value'],
						'#size' => 20,
					),
					'c22' => array(
						'#type' => 'textfield',
						'#size' => 10,
						'#default_value' => $options_node->field_option_comments['und'][0]['value'],
					),
					'c23' => array(
						'#type' => 'textfield',
						'#size' => 10,
						'#default_value' => $options_node->field_option_trip['und'][0]['value'],
					),
				),
			);
		}else{
			$hsr_row[$hotel_id] = array(
				'#tree' =>TRUE,
				$hotel_id => array(  //Generating unique array id for every form element
					'c1' =>array(
						'#type' => 'checkbox',
					),
					'c2' =>array(
						'#type' => 'markup',
						'#markup' => '<h4 style = "text-align: left !important;" class = "hotel_name">'. $array['name'] .'</h4>',
					),
					'c3' =>array(
						'#type' => 'markup',
						'#markup' => '<h4 style = "text-align: left !important;">'. $array['room_type'] .'</h4>',
					),
					'c4' =>array(
						'#type' => 'markup',
						'#markup' => '<h4 style = "text-align: left !important;">'. $array['bedding'] .'</h4>',
					),
					'c5' =>array(
						'#type' => 'markup',
						'#markup' => '<h4 style = "text-align: left !important;">'. $array['field_max_occupancy'] .'</h4>',
					),
					'c6' => array(
						'#type' => 'textfield',
						'#size' => 5,
						'#disabled' => TRUE,
						'#required' => TRUE,
					),
					'c7' =>array(
						'#type' => 'markup',
						'#markup' => '<h4 style = "text-align: left !important;">'. $array['scr'] .'</h4>',
					),
					'c8' =>array(
						'#type' => 'markup',
						'#markup' => '<h4 style = "text-align: left !important;">'. $array['rate_slab_name'] .'</h4>',
					),
					'c9' => array(
						'#type' => 'select',
						'#options' => drupal_map_assoc(array('No', 'Yes')),
						'#default_value' => $array['internet'],
						'#disabled' => TRUE,
						'#chosen' => FALSE,
					),
					'c10' => array(
						'#type' => 'textfield',
						'#size' => 5,
						'#disabled' => TRUE,
					),
					'c11' => array(
						'#type' => 'select',
						'#options' => drupal_map_assoc(array('No', 'Yes')),
						'#default_value' => $array['breakfast'],
						'#disabled' => TRUE,
						'#chosen' => FALSE,
					),
					'c12' => array(
						'#type' => 'textfield',
						'#size' => 5,
						'#disabled' => TRUE,
					),
					'c13' => array(
						'#type' => 'markup',
						'#markup' => '<h4 style = "text-align: left !important;">'. $array['city'] .'</h4>',
					),
					'c14' => array(
						'#type' => 'select',
						'#options' => $currencies,
						'#default_value' => $array['currency'],
						'#disabled' => TRUE,
						'#chosen' => FALSE,
						'#required' => TRUE,
					),
					'c15' => array(
						'#type' => 'textfield',
						'#default_value' => $array['net_rate'],
						'#size' => 5,
						'#disabled' => TRUE,
						'#required' => TRUE,
					),
					'c16' => array(
						'#type' => 'textfield',
						'#size' => 20,
						'#disabled' => TRUE,
						'#required' => TRUE,
					),
					'c17' => array(
						'#type' => 'checkbox',
						'#default_value' => $array['tax'],
						'#disabled' => TRUE,
					),
					'c18' => array(
						'#type' => 'textfield',
						'#default_value' => $array['cancel'],
						'#size' => 30,
						'#disabled' => TRUE,
					),
					'c19' => array(
						'#type' => 'select',
						'#options' => $array['pp'],
						'#disabled' => TRUE,
						'#chosen' => FALSE,
						'#required' => TRUE,
					),
					'c20' => array(
						'#type' => 'textfield',
						'#size' => 20,
						'#disabled' => TRUE,
					),
					'c21' => array(
						'#type' => 'textfield',
						'#default_value' => $array['amenities'],
						'#size' => 20,
						'#disabled' => TRUE,
					),
					'c22' => array(
						'#type' => 'textfield',
						'#size' => 10,
						'#disabled' => TRUE,
					),
					'c23' => array(
						'#type' => 'textfield',
						'#size' => 10,
						'#disabled' => TRUE,
					),
				),
			);
		}
	}

	$form['hsr']['filter_wrapper'] = array(
		'#type' => 'container',
		'#prefix' => '<div id = "filter_wrapper">',
		'#suffix' => '</div>',
	);

	$form['hsr']['filter_wrapper']['hotels'] = array(
		'#theme' => 'leads_hsr_table',
		'rows' => $hsr_row,
		'#prefix' => '<div id = "testing">',
		'#suffix' => '</div>',
	);

	$form['vof'] = array(
		'#type' => 'submit',
		'#value' => 'View Options Form',
	);

	$form['save'] = array(
		'#type' => 'submit',
		'#value' => 'Save Form',
	);
	return $form;
}

/**
 *This function applies filter
 */
function apply_filter_ajax($form, &$form_state){
	return $form['hsr']['filter_wrapper'];
}

/**
 *Theme function
 */
function theme_leads_hsr_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t('Select'), t('Hotel'), t('Room Type'), t('Bedding'), t('Max Occupancy'), t('Actual Occupancy'), t('Special Contract Rate'),
				t('Rate Slab'), t('Internet'), t('Internet Cost'), t('Breakfast'), t('Breakfast Cost'), t('Location'), t('Currency'), t('Rate'), t('Source of Rate'),
				t('Does rate include tax?'), t('Cancellation Policy'), t('Payment Policies'), t('Distance from Work Location'), t('Amenities'),
				t('Comments'), t('Trip Advisor Reviews'));

  // Setup the structure to be rendered and returned.
  $content = array(
    '#theme' => 'table',
    '#rows' => array(),
    '#header' => $header,
  );

  // Traverse each row.  @see element_chidren().
  foreach (element_children($rows) as $row_index) {
    $row = array();
    // Traverse each column in the row.  @see element_children().
    foreach (element_children($rows[$row_index]) as $col_index) {
      // Traverse each column in the row.  @see element_children().
      foreach (element_children($rows[$row_index][$col_index]) as $col_index1) {
      // Render the column form element.
        $row[] = drupal_render($rows[$row_index][$col_index][$col_index1]);
      }
    }
    // Add the row to the table.
    $content['#rows'][] = $row;
  }

  // Redner the table and return.
  return drupal_render($content);
}

/**
 *Theme function
 */
function theme_leads_table(&$variables){
  // Get the useful values.
  $form = $variables['form'];
  $rows = $form['rows'];
  $header = array(t('TN No.'), t('Check In'), t('Check Out'), t('No. of Nights'), t('Location'), t('Guest Names'),
									t('No. of Adults'), t('No. of Children'), t('No. of Infants'), t('Status'), t('Actions'));

  // Setup the structure to be rendered and returned.
  $content = array(
    '#theme' => 'table',
    '#rows' => array(),
    '#header' => $header,
  );

  // Traverse each row.  @see element_chidren().
  foreach (element_children($rows) as $row_index) {
    $row = array();
    // Traverse each column in the row.  @see element_children().
    foreach (element_children($rows[$row_index]) as $col_index) {
      // Traverse each column in the row.  @see element_children().
      foreach (element_children($rows[$row_index][$col_index]) as $col_index1) {
      // Render the column form element.
        $row[] = drupal_render($rows[$row_index][$col_index][$col_index1]);
      }
    }
    // Add the row to the table.
    $content['#rows'][] = $row;
  }

  // Redner the table and return.
  return drupal_render($content);
}
