<?php

/**
 * @file
 * template.php
 */

define('JS_BOOTSTRAP_MATERIAL', 200);
 
 
/**
 * Preprocess html.tpl.php.
 *
 * @see bootstrap_material_js_alter()
 */
function bootstrap_material_preprocess_html(&$vars) {
  // Add class to help us style admin pages.
  if (path_is_admin(current_path())) {
    $vars['classes_array'][] = 'admin';
  }
  // Prepare to initialize.
  drupal_add_js('(function ($){ $.material.init(); })(jQuery);', array(
    'type' => 'inline', 
    'group' => JS_BOOTSTRAP_MATERIAL, 
    'scope' => 'footer', 
    'weight' => 2
  ));
  
  drupal_add_css('https://fonts.googleapis.com/icon?family=Material+Icons');
  drupal_add_css('https://fonts.googleapis.com/css?family=Roboto:regular,bold,italic,thin,light,bolditalic,black,medium&amp;lang=en');
}

function bootstrap_material_links__system_main_menu($variables) {
  //kpr($variables);
  //kpr($main_menu_expanded);
  $menu_tree = menu_tree_all_data('main-menu');
  $main_mn = menu_tree_output($menu_tree);
  //kpr($menu_tree);
  //print render($main_mn);
  $links = $variables['links'];
  $attributes = $variables['attributes'];
  $heading = $variables['heading'];
  global $language_url;
  $output = '';

  if (count($links) > 0) {
    // Treat the heading first if it is present to prepend it to the
    // list of links.
    if (!empty($heading)) {
      if (is_string($heading)) {
        // Prepare the array that will be used when the passed heading
        // is a string.
        $heading = array(
          'text' => $heading,
          // Set the default level of the heading.
          'level' => 'h2',
        );
      }
      $output .= '<' . $heading['level'];
      if (!empty($heading['class'])) {
        $output .= drupal_attributes(array('class' => $heading['class']));
      }
      $output .= '>' . check_plain($heading['text']) . '</' . $heading['level'] . '>';
    }

    //$output .= '<ul' . drupal_attributes($attributes) . '>';

    $num_links = count($links);
    $i = 1;

    foreach ($links as $key => $link) {
      $class = array($key);
      //kpr($link);
      // Add first, last and active classes to the list of links to help out
      // themers.
      if ($i == 1) {
        $class[] = 'first';
      }
      if ($i == $num_links) {
        $class[] = 'last';
      }
      if (isset($link['href']) && ($link['href'] == $_GET['q'] || ($link['href'] == '<front>' && drupal_is_front_page()))
         && (empty($link['language']) || $link['language']->language == $language_url->language)) {
        $class[] = 'active';
      }
      //$output .= '<li' . drupal_attributes(array('class' => $class)) . '>';
      $mid = substr($key, 5);
      if (isset($link['href'])) {
        // Pass in $link as $options, they share the same keys.
        //$output .= l($link['title'], $link['href'], $link, array('attributes' => array('class' => 'mdl-navigation__link')));
        global $base_url;
        if($link['href'] == '<front>'){
          $path = $base_url;
          $output .= '<a class = "mdl-navigation__link" href = "'.$path.'"><i class="mdl-color-text--blue-grey-400 material-icons">'.'home</i>'.$link['title'].'</a>';
        }else{
          if((substr($link['href'], 0, 7) === 'http://')){
            $path = $link['href'];
            $output .= '<a class = "mdl-navigation__link" href = "'.$path.'" target="_blank"><i class="mdl-color-text--blue-grey-400 material-icons">'.'home</i>'.$link['title'].'</a>';
          }else{
            $path = $base_url.'/'.$link['href'];
            $output .= '<a class = "mdl-navigation__link" href = "'.$path.'" style="text-decoration: none;"><i class="mdl-color-text--blue-grey-400 material-icons">'.'home</i>'.$link['title'].'</a>';
          }
        }
      }elseif (!empty($link['title'])) {
        // Some links are actually not links, but we wrap these in <span> for
        // adding title and class attributes.
        if (empty($link['html'])) {
          $link['title'] = check_plain($link['title']);
        }
        $span_attributes = '';
        if (isset($link['attributes'])) {
          $span_attributes = drupal_attributes($link['attributes']);
        }
        $output .= '<span' . $span_attributes . '>' . $link['title'] . '</span>';
      }
      foreach($menu_tree as $menu_data){
        if($menu_data['link']['mlid'] == $mid){
          if($menu_data['below'] != NULL){
            
          }
        }
      }
      $i++;
      //$output .= "</li>\n";
    }

    //$output .= '</ul>';
  }

  return $output;
}
/**
 * Implements hook_js_alter().
 *
 * Make sure the library files provided by MDB load last, then initialize.
 *
 * @see bootstrap_material_preprocess_html()
 */
function bootstrap_material_js_alter(&$js) { 
  
  $file = path_to_theme() . '/js/bootstrap_material.js';
  
  $js[$file] = drupal_js_defaults($file);
  $js[$file]['group'] = JS_BOOTSTRAP_MATERIAL;
  $js[$file]['scope'] = 'footer';
  $js[$file]['weight'] = $weight = 0;
  
  // Ensure we initialize only after files are loaded.
  foreach ($js as $key => $val) {
    if (is_int($key) && $val['group'] == JS_BOOTSTRAP_MATERIAL) {
      $weight++;
      $js[$key]['weight'] = $weight;
    }
  }
}

/**
 * Overrides theme_menu_local_tasks().
 *
 * Overrides Bootstrap module's override. Let's not turn the secondary menu 
 * into a pagination element.
 *
 * @see bootstrap_menu_local_tasks()
 */
function bootstrap_material_menu_local_tasks(&$variables) {
  $output = '';

  if (!empty($variables['primary'])) {
    $variables['primary']['#prefix'] = '<h2 class="element-invisible">' . t('Primary tabs') . '</h2>';
    $variables['primary']['#prefix'] .= '<ul class="tabs--primary nav nav-tabs">';
    $variables['primary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['primary']);
  }

  if (!empty($variables['secondary'])) {
    $variables['secondary']['#prefix'] = '<h2 class="element-invisible">' . t('Secondary tabs') . '</h2>';
    $variables['secondary']['#prefix'] .= '<ul class="tabs--secondary">';
    $variables['secondary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['secondary']);
  }

  return $output;
}

/**
 * Overrides theme_menu_local_action().
 *
 * Overrides Bootstrap module's override. All we're doing is making the action
 * link buttons bigger by removing the 'btn-xs' class.
 *
 * @see bootstrap_menu_local_action()
 */
function bootstrap_material_menu_local_action($variables) {
  $link = $variables['element']['#link'];

  $options = isset($link['localized_options']) ? $link['localized_options'] : array();

  // If the title is not HTML, sanitize it.
  if (empty($options['html'])) {
    $link['title'] = check_plain($link['title']);
  }

  $icon = _bootstrap_iconize_text($link['title']);

  // Format the action link.
  $output = '';
  if (isset($link['href'])) {
    // Turn link into a mini-button and colorize based on title.
    if ($class = _bootstrap_colorize_text($link['title'])) {
      if (!isset($options['attributes']['class'])) {
        $options['attributes']['class'] = array();
      }
      $string = is_string($options['attributes']['class']);
      if ($string) {
        $options['attributes']['class'] = explode(' ', $options['attributes']['class']);
      }
      $options['attributes']['class'][] = 'btn';
      $options['attributes']['class'][] = 'btn-' . $class;
      if ($string) {
        $options['attributes']['class'] = implode(' ', $options['attributes']['class']);
      }
    }
    // Force HTML so we can render any icon that may have been added.
    $options['html'] = !empty($options['html']) || !empty($icon) ? TRUE : FALSE;
    $output .= l($icon . $link['title'], $link['href'], $options);
  }
  else {
    $output .= $icon . $link['title'];
  }

  return $output;
}
