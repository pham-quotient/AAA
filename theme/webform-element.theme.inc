<?php
/**
 * Replacement for theme_form_element().
 */
function si_aaa_webform_element($variables) {
	//dpm($variables);
  $element = $variables['element'];
	//$element['#wrapper_attributes']['class'][] = $element['#required'] ? 'requried' : '';
  $output = $element['#type'] == 'radios' || $element['#type'] == 'checkboxes' ? '<fieldset ' . drupal_attributes($element['#wrapper_attributes']) . '>' . "\n":
						'<div ' . drupal_attributes($element['#wrapper_attributes']) . '>' . "\n";
  $prefix = isset($element['#field_prefix']) ? '<span class="field-prefix">' . webform_filter_xss($element['#field_prefix']) . '</span> ' : '';
  $suffix = isset($element['#field_suffix']) ? ' <span class="field-suffix">' . webform_filter_xss($element['#field_suffix']) . '</span>' : '';

  // Generate description for above or below the field.

	$description = !empty($element['#description']) ? ' <div class="description">' . $element['#description'] . "</div>\n" : '';
	$form_item = $prefix . $element['#children'] . $suffix . "\n";
	if ($element['#type'] == 'textfield' || $element['#type'] == 'webform_email' ||  $element['#type'] == 'webform_number') {
		$form_item = '<div class="form-textfield-wrapper">'. $form_item .'</div>';
	}
  //dpm($variables);
  switch ($element['#title_display']) {
    case 'inline':
    case 'before':
    case 'invisible':
      $output .= $element['#type'] == 'radios' || $element['#type'] == 'checkboxes' ? theme('form_element_label', $variables) : ' <div class="form-label-wrapper">' . theme('form_element_label', $variables);
			$output .=  $element['#type'] == 'radios' || $element['#type'] == 'checkboxes' ? $description : $description .'</div>';
      $output .= ' ' . $form_item;
      break;

    case 'after':
      $output .= ' ' . $form_item;
      $output .= $element['#type'] == 'radios' || $element['#type'] == 'checkboxes' ? theme('form_element_label', $variables) :  ' <div class="form-label-wrapper">' . theme('form_element_label', $variables);
			$output .=  $element['#type'] == 'radios' || $element['#type'] == 'checkboxes' ? $description : $description .'</div>';
      break;

    case 'none':
    case 'attribute':
      // Output no label and no required marker, only the children.
      $output .= ' ' . $form_item;
      break;
  }

  $output .= $element['#type'] == 'radios' || $element['#type'] == 'checkboxes' ? "</fieldset>\n" : "</div>\n";
  return $output;

}
