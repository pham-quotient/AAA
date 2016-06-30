<?php

/**
 * Implements hook_preprocess_page().
 */
function si_aaa_preprocess_edan_search_results(&$vars) {
	_render_edan_search_results($vars);

}