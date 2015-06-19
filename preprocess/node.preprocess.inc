<?php

/**
 * Implements hook_preprocess_page().
 */
function si_aaa_preprocess_node(&$variables) {
  // You can use preprocess hooks to modify the variables before they are passed
  // to the theme function or template file.
	$node = $variables ['node'];
	if ($node->type == 'carousel_slide') {
		$content = $variables['content'];
		$classes = array();
		$classes[] = empty($node->field_image) ? 'solid-bg' : 'overlay';
		$classes[] = 'slide-inner';
		$field_name = 'field_link_single';
		$langcode = field_language('node', $node, $field_name, NULL);
		$item = $node->$field_name;
		$item = current($item[$langcode]);
		$path = array_shift($item);
		unset($item['title']);
 		$attributes = array_shift($item); 
		$attributes['class'] = $classes;
		$variables['link_attributes'] = drupal_attributes($attributes);
		$variables['link_url'] = url($path, $item);
		$variables['slide_image'] = empty($node->field_image) ? '' : $content['field_image']['#items'][0];
//		unset($variables['title']);
	
	}
}
