<?php
/**
 * @file
 * Template for a 2 column panel layout.
 *
 * This template provides a two column panel display layout, with
 * each column roughly equal in width. It is 5 rows high; the top
 * middle and bottom rows contain 1 column, while the second
 * and fourth rows contain 2 columns.
 *
 * Variables:
 * - $id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout. This layout supports the following sections:
 *   - $content['top']: Content in the top row.
 *   - $content['left_above']: Content in the left column in row 2.
 *   - $content['right_above']: Content in the right column in row 2.
 *   - $content['middle']: Content in the middle row.
 *   - $content['left_below']: Content in the left column in row 4.
 *   - $content['right_below']: Content in the right column in row 4.
 *   - $content['right']: Content in the right column.
 *   - $content['bottom']: Content in the bottom row.
 */
?>
<div class="panel-display panel-2col-bricks clearfix" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>
  <?php if ($content['top']): ?>
    <div class="panel-col-top panel-panel">
      <div class="inside">
        <?php print $content['top']; ?>
      </div>
    </div>
  <?php endif; ?>

  <?php if ($content['left_above'] || $content['right_above']): ?>
    <div class="center-wrapper">
      <div class="inside">
        <?php if ($content['left_above']): ?>
          <div class="panel-col-first panel-panel<?php $content['right_above'] ? print ' has-right-content' : ''?>">
            <?php print $content['left_above']; ?>
          </div>
        <?php endif; ?>
        <?php if ($content['right_above']): ?>
        <div class="panel-col-last panel-panel<?php $content['left_above'] ? print 'has-left-content' : ''?>">
          <?php print $content['right_above']; ?>
        </div>
        <?php endif; ?>
      </div>
    </div>
  <?php endif; ?>

  <?php if ($content['middle']): ?>
    <div class="panel-panel panel-col-middle">
      <div class="inside">
        <?php print $content['middle']; ?>
      </div>
    </div>
  <?php endif; ?>

  <?php if ($content['left_below'] || $content['right_below']): ?>
    <div class="center-wrapper">
      <div class="inside">
        <?php if ($content['left_below']): ?>
          <div class="panel-col-first panel-panel<?php $content['right_below'] ? print ' has-right-content' : ''?>">
            <?php print $content['left_below']; ?>
          </div>
        <?php endif; ?>
        <?php if ($content['right_below']): ?>
        <div class="panel-col-last panel-panel<?php $content['left_below'] ? print 'has-left-content' : ''?>">
          <?php print $content['right_below']; ?>
        </div>
        <?php endif; ?>
      </div>
    </div>
  <?php endif; ?>
  <?php if ($content['bottom']): ?>
    <div class="panel-col-bottom panel-panel">
      <div class="inside">
        <?php print $content['bottom']; ?>
      </div>
    </div>
  <?php endif; ?>
</div>
