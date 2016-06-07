<?php

/**
 * Returns HTML for a date element formatted as a range.
 * Overrides theme_date_display_range
 */
function si_aaa_date_display_range($variables) {
  $dates = $variables['dates'];
  $date1 = $variables['date1'];
  $date2 = $variables['date2'];
  $time1 = preg_replace('`^([\(\[])`', '', $dates['value']['formatted_time']);
  $time1 = preg_replace('([\)\]]$)', '', $time1);
  $time2 = preg_replace('`^([\(\[])`', '', $dates['value2']['formatted_time']);
  $time2 = preg_replace('([\)\]]$)', '', $time2);
  $timezone = $variables['timezone'];

  if ($date1 == $time1 || empty($time1)) {
    $attributes_start = $variables['attributes_start'];
    $attributes_end = $variables['attributes_end'];

    $start_date = '<span class="date-display-start"' . drupal_attributes($attributes_start) . '>' . $date1 . '</span>';
    $end_date = '<span class="date-display-end"' . drupal_attributes($attributes_end) . '>' . $date2 . $timezone . '</span>';

    // If microdata attributes for the start date property have been passed in,
    // add the microdata in meta tags.
    if (!empty($variables['add_microdata'])) {
      $start_date .= '<meta' . drupal_attributes($variables['microdata']['value']['#attributes']) . '/>';
      $end_date .= '<meta' . drupal_attributes($variables['microdata']['value2']['#attributes']) . '/>';
    }
		$out = t('!start-date - !end-date', array(
      '!start-date' => $start_date,
      '!end-date' => $end_date,
    ));
    // Wrap the result with the attributes.
    return '<span class="date-display-wrapper">'.
			$out .'</span>';
  }
  else {
		$dateObject1 = $dates['value']['db']['object'];
		$dateObject2= $dates['value2']['db']['object'];
		$year1 = date_format($dateObject1, 'Y');
		$year2 = date_format($dateObject2, 'Y');
		if ($year1 == $year2) {
			$day1 = explode(',', $dates['value']['formatted_date']);
    	$day1 = trim(current($day1));
		}
		else {
			$day1 = $dates['value']['formatted_date'];
		}
    $day2 = $dates['value2']['formatted_date'];
    $day_range = '<span class="date-display-day-range">' . $day1 . ' to '. $day2 .'</span>';
    $time_range = $time1 == 'All day' ? '' : '<span class="date-display-time-range">' . $time1 . ' - '. $time2  . $timezone .'</span>';
    return t('!day-range !time-range', array(
      '!day-range' => $day_range,
      '!time-range' => $time_range
    ));
  }
}
