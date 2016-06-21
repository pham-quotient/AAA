<?php

/**
 * Implements hook_preprocess_ogmt_edan_search_results().
 */
function si_aaa_preprocess_ogmt_edan_search_results(&$vars) {
	_render_edan_search_results($vars);
}