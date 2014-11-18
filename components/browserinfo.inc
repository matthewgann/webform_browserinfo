<?php
  //see https://github.com/cbschuld/Browser.php/blob/master/README.md
  //see http://jamestombs.co.uk/2012-09-24/create-new-webform-element-drupal-7
require('browser.php');


function _webform_defaults_browserinfo() {
  return array(
    'name' => '',
    'form_key' => NULL,
    'pid' => 0,
    'weight' => 0,
    'value' => '',
    'mandatory' => 0,
    'extra' => array(
      'field_prefix' => '',
      'field_suffix' => '',
    ),
  );
}

function _webform_theme_browserinfo() {
  return array(
    'webform_display_browserinfo' => array(
      'render element' => 'element',
    ),
  );
}

function _webform_render_browserinfo($component, $value = NULL, $filter = TRUE) {
  $browser = new Browser();
  $browserinfo = $browser->getBrowser() . " " . $browser->getVersion() . " on " . $browser->getPlatform();

  $node = isset($component['nid']) ? node_load($component['nid']) : NULL;
  $element = array(
    '#title' => $filter ? webform_filter_xss($component['name']) : $component['name'],
    '#title_display' => $component['extra']['title_display'] ? $component['extra']['title_display'] : 'before',
    '#type' => 'textfield',
    '#disabled' => TRUE,
    '#default_value' => $browserinfo,
    '#required' => $component['mandatory'],
    '#weight' => $component['weight'],
    '#theme_wrappers' => array('webform_element'),
    '#field_prefix' => empty($component['extra']['field_prefix']) ? NULL : ($filter ? webform_filter_xss($component['extra']['field_prefix']) : $component['extra']['field_prefix']),
    '#field_suffix' => empty($component['extra']['field_suffix']) ? NULL : ($filter ? webform_filter_xss($component['extra']['field_suffix']) : $component['extra']['field_suffix']),
    '#description' => $filter ? webform_filter_descriptions($component['extra']['description'], $node) : $component['extra']['description'],
    '#attributes' => $component['extra']['attributes'],

  );
  return $element;
}

function _webform_display_browserinfo($component, $value, $format = 'html') {
  return array(
    '#title' => "Browser Information",
    '#weight' => $component['weight'],
    '#theme' => 'webform_display_browserinfo',
    '#theme_wrappers' => $format == 'html' ? array('webform_element') : array('webform_element_text'),
    '#format' => $format,
    '#value' => $value[0],
    '#translatable' => array('title', 'field_prefix', 'field_suffix'),
  );
}

function theme_webform_display_browserinfo($variables) {
  $element = $variables['element'];
  $value = $element['#value'];
  return trim($value) !== '' ? $value : ' ';
}

function _webform_table_browserinfo($component, $value) {
  return check_plain(empty($value[0]) ? '' : $value[0]);
}

function _webform_csv_headers_browserinfo($component, $export_options) {
  $header = array();
  $header[0] = 'Browser Information';
  return $header;
}
?>