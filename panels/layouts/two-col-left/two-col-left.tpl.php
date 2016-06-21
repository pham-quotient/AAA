<?php
/**
 * @file
 * Template for the Omega Grid 3 layout.
 *
 * Variables:
 * - $css_id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 * panel of the layout. This layout supports the following sections:
 */
?>
<div<?php print $attributes ?>>
  <?php if (!empty($content['hero'])): ?>
    <div<?php print drupal_attributes($region_attributes_array['hero'])?>>
      <?php print $content['hero'] ?>
    </div>
  <?php
    unset($content['hero']);
  endif; ?>
  <?php if (!empty($content)): ?>

      <?php if (!empty($content['main']) || !empty($content['tab']) || !empty($content['bottom'])): ?>
        <div class="l-region--main<?php print !empty($variables['content']['left']) ? ' has-sidebar-first' : ''?>">
          <?php if (!empty($content['main'])): ?> 
            <div<?php print drupal_attributes($region_attributes_array['main'])?>> 
              <?php print $content['main'] ?> 
            </div> 
          <?php endif; ?>
          <?php if (!empty($content['tab']) || !empty($content['bottom'])): ?>
            <div class="l-pane-wrapper<?php print !empty($content['bottom']) ? ' has-bottom-content' : '' ?>">
              <?php if (!empty($content['tab'])): ?>  
                <div<?php print drupal_attributes($region_attributes_array['tab'])?>>  
                  <?php print $content['tab'] ?>  
                </div>  
              <?php endif; ?>
              <?php if (!empty($content['bottom'])): ?>  
                <div<?php print drupal_attributes($region_attributes_array['bottom'])?>>  
                  <?php print $content['bottom'] ?>  
                </div>  
              <?php endif; ?>               
            </div>
          <?php endif; ?>
        </div>
      <?php endif; ?>

      <?php if (!empty($content['left'])): ?>
        <aside<?php print drupal_attributes($region_attributes_array['left'])?>>
          <?php print $content['left'] ?>
        </aside>
      <?php endif; ?>
  <?php endif; ?>

</div>
