<?php 
//  dpm($variables);
?>
<!-- Remove Facets Links -->
<?php if($active_facets): ?>
  <div id="remove_facets_links">
    <?php print $active_facets; ?>
  </div>
<?php endif; ?>

<!-- Render the Filter Tab Menus -->
<?php if($filter_menus['tabs']): ?>
  <div class="edan-facets">
    <?php print drupal_render($filter_menus['tabs']); ?>
  </div>
<?php endif; ?>
<div class="edan-search-prefix">
    <?php print $pager; ?>
    <div class="edan-results-summary"><?php print($results_summary); ?></div>
  
  <div class="toggle-view">
  </div>
</div>
<div class="edan-search-wrapper <?php print variable_get('si_edan_default', 'list-view'); ?>">
  <div class="<?php print $container_class; ?>">
    <ul class="search-results<?php print $results_class; ?>">
      <?php foreach ($docs as $doc): ?>
        <li <?php print drupal_attributes($doc['row_attributes']); ?>>
          <div class="edan-row">

              <a href="<?php print $doc['local_record_link']; ?>" class="result-overivew">
              <div class="edan-record-type"><?php print $doc['record_type']; ?></div>
              <?php if(!empty($doc['newMedia'])): ?>
                <div class="thumbnail">
                  <img src="<?php print $doc['newMedia']['thumbnail'];?>" alt="thumbnail image for <?php print $doc['record_title']; ?>">
                </div>
              <?php endif; ?>
              <div class="overview-info">
                <h3 class="object-title"><?php print $doc['record_title']; ?></h3>
                <?php if ($doc['date']): ?>
                  <div class="edan-date"><?php print $doc['date']; ?></div>
                <?php endif; ?>

              </div>
              </a>
            <?php if(module_exists('devel') && isset($_GET['dpm']) && user_access('access devel information')):
              dpm($doc);
            elseif (isset($_GET['dump'])):
              print '<pre>' . var_export($doc, TRUE) . '</pre>';
            endif; ?>
          </div>
        </li>
      <?php endforeach; ?>

    </ul>
  </div>

</div>
<div class="edan-search-footer">
  <?php print $pager; ?>
</div>

