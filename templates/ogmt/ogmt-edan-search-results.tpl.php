<?php 
  dpm($variables);
?>
<!-- Remove Facets Links -->
<?php if($active_facets): ?>
  <div id="remove_facets_links">
    <?php print $active_facets; ?>
  </div>
<?php endif; ?>

<!-- Render the Filter Tab Menus -->
<?php if($filter_menus['tabs']): ?>
  <?php print drupal_render($filter_menus['tabs']); ?>
<?php endif; ?>

<div class="edan-search clearfix <?php print variable_get('si_edan_default', 'list-view'); ?>">

  <?php echo $pager; ?>

  <div class="edan-results-summary"><?php print($results_summary); ?></div>
  <div class="<?php print $container_class; ?>">
    <ul class="search-results<?php print $results_class; ?>">
      <?php
      foreach ($docs as $doc): ?>

        <li <?php print drupal_attributes($doc['row_attributes']); ?>>
          <div class="edan-row">
            <span class="edan-search-mini-toggle button">Expand</span>
            <div class="result-overivew">
              <?php if(isset($doc['newMedia'])): ?>
                <div class="thumbnail">
                  <a href=""><img src="" alt="thumbnail image for <?php print $doc['##title_plain']"></a>
                </div>
              <?php endif; ?>
              <a href="' . $doc_value['local_record_link'] . '">
                <h3 class="title"><?php echo $doc['#title_plain']; ?></h3>
              </a>
            </div>
          <?php if(module_exists('devel') && isset($_GET['dpm']) && user_access('access devel information')) {
            dpm($doc);
          }
          else if (isset($_GET['dump'])) {
            echo '<pre>' . var_export($doc, TRUE) . '</pre>';
          }
          else { ?>

          <?php if (isset($doc['content']['descriptiveNonRepeating']['online_media']['media'])): ?>
          <a href="<?php echo $doc['content']['descriptiveNonRepeating']['online_media']['media'][0]['content']; ?>" class="thumbnail"><img src="<?php echo $doc['content']['descriptiveNonRepeating']['online_media']['media'][0]['thumbnail']; ?>" alt="" /></a>
          <?php endif; ?>

          <?php
            // render the geoLocation from structured data, if available
            // note, to see a nicer view of this nested array, if Devel is enabled on the site, uncomment this:
            // dpm($doc['content']);
            if(array_key_exists('indexedStructured', $doc['content'])) :
              // create a template for the array we're expecting:
              $structuredIndexTemplate = array(
                'geoLocation' => array(
                  0 => array(
                    'points' => array(
                      'point' => array (
                        'latitude' => array(
                          'content'
                        ),
                        'longitude' => array(
                          'content'
                        )
                      )
                    )
                  )
                )
              );
              $structuredIndex = array_merge($structuredIndexTemplate, $doc['content']['indexedStructured']);
              $latitude = isset($structuredIndex['geoLocation'][0]['points']['point']['latitude']['content'])
                ? $structuredIndex['geoLocation'][0]['points']['point']['latitude']['content']
                : '';
              $longitude = isset($structuredIndex['geoLocation'][0]['points']['point']['longitude']['content'])
                ? $structuredIndex['geoLocation'][0]['points']['point']['longitude']['content']
                : '';

              $field = 'geoLocation_0';
              // if you're expecting multiple locations, adjust the $structuredIndexTemplate, and use the array key instead of hard-coding 0 in the $field

              // now render it:
              if(strlen($latitude) > 0 || strlen($longitude) > 0) : ?>
              <dl class="edan-search-<?php echo $field; ?>">
                <dt><?php echo t('Geographic Location'); ?></dt>
                <dd><?php echo ($latitude . ', ' . $longitude); ?></dd>
              </dl>
              <?php
              endif;
            endif;

          ?>

          <?php foreach ($doc['content']['freetext'] as $field => $vals): ?>
          <dl class="edan-search-<?php echo $field; ?>">
            <?php $current_label = ''; ?>
            <?php foreach ($vals as $value): ?>
              <?php if ($value['label'] != $current_label): ?>
            <dt><?php echo $value['label']; ?></dt><?php $current_label = $value['label']; ?>
              <?php endif; ?>
            <dd><?php echo $value['content']; ?></dd>
            <?php endforeach; ?>
          </dl>
          <?php endforeach; ?>
          <?php } // End If ?>
        </div>
      </li>
      <?php endforeach; ?>

    </ul>
  </div>

  <?php if ($facets): ?>
  <?php
    // $facets contains the formatted facet content
    // $facets_raw is an array of facet data, which can be used for custom formatting facets
    // $active_facets_raw is an array of the currently active/selected facets
  ?>
  <div class="edan-search-facets">
    <?php echo $facets; ?>
  </div>
  <?php endif; ?>

  <?php echo $pager; ?>
</div>