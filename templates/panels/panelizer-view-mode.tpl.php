<?php
// @todo document this!
?>

<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php print render($title_prefix); ?>
  <?php if (!empty($title)): ?>
    <<?php print $title_element;?> <?php print $title_attributes; ?>>
      <?php print $title; ?>
    </<?php print $title_element;?>>
  <?php endif; ?>
  <?php print render($title_suffix); ?>
  <?php print $content; ?>
</div>