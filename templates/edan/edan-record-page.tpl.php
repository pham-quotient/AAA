<?php
/**
 * Theme Individual Object Page
 */
   // dpm($variables);
?>




  <div class="edan-object-wrapper">
		<?php if ($si_header): ?>
      <div class="l-region--hero">
        <?php print $si_header; ?>
      </div>
    <?php endif; ?>

    <?php
   //   if ($breadcrumb) {
   //     print $breadcrumb;
   //   }
    ?>
 	<div class="l-container">
  	<div class="preface--edan-object">
    	<div class="link-wrapper">

          <ul class="links">
              <?php if($back_link):     ?>
                <li class="back-link"><?php print $back_link; ?></li>
              <?php endif; ?>
              <li>
              <a class="print button" href="javascript:window.print()">
                <span>Print</span>
              </a>
            </li>
          </ul>
        </div>
        <?php if($search_form): ?>
          <div class="collection-search-form">
            <?php print render($search_form); ?>
          </div>
        <?php endif; ?>
    </div>


		<?php foreach ($docs as $doc):
      $mediaFloat = TRUE; ?>
    	<div <?php print drupal_attributes($doc['row_attributes']); ?>>
        <div class="edan-row">
          <h1 class="title"><?php isset($doc['#title_plain']) ? print t($doc['#title_plain']) : 	print $doc['#title']; ?></h1>
          <?php if (isset($_GET['dump'])): ?>
            <?php print '<pre>' . var_export($doc, TRUE) . '</pre>';
              else: ?>


          <?php if (!empty($doc['content']['media'])):
            $media = _media_theme($doc['content']['media']);
            $mediaFloat = $media['mediaFloat']; ?>

            <div class="record-media<?php print $mediaFloat ? ' no-slideshow' : ' has-slideshow'; ?>">
              <?php print $media['content']; ?>
            </div>
            <div class="record-details<?php print $mediaFloat ? ' no-slideshow' : ' has-slideshow'; ?>">
              <?php foreach ($doc['content']['freetext'] as $field => $vals): ?>
                <dl class="edan-search-<?php print $field; ?>">
                  <?php $current_label = ''; ?>
                  <?php foreach ($vals as $value): ?>
                    <?php if ($value['label'] != $current_label): ?>
                  <dt><?php print $value['label']; ?></dt><?php $current_label = $value['label']; ?>
                    <?php endif; ?>
                  <dd><?php print $value['content']; ?></dd>
                  <?php endforeach; ?>
                </dl>
              <?php endforeach; ?>
            </div>
          <?php endif; ?>
        <?php endif; ?>
      </div>
    </div>
  <?php endforeach; ?>



</div>
