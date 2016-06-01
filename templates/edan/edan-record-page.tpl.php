<?php
// dumper($docs);
$class = (isset($docs['flags']['in_list']) && $docs['flags']['in_list'] === TRUE) ? ' in-list' : '';
?>

<?php if(isset($docs['content']['descriptiveNonRepeating'])) : ?>
  <div class="edan-record-container edan-search-result<?php print $class; ?>" id="<?php echo $docs['content']['descriptiveNonRepeating']['record_ID']; ?>">
    <div class="edan-row">
      <?php if (isset($docs['content']['descriptiveNonRepeating']['online_media']['media'])): ?>
      <img src="<?php echo $docs['content']['descriptiveNonRepeating']['online_media']['media'][0]['thumbnail']; ?>" alt="" class="thumbnail" />
      <?php endif; ?>

      <?php
      foreach ($docs['content']['freetext'] as $field => $vals) {
        $current_label = '';
        echo '<dl class="edan-search-' . $field . '">' . "\n";
        foreach ($vals as $value) {
          if ($value['label'] !== $current_label) {
            echo '<dt>' . $value['label'] . '</dt>' . "\n";
          }
          $current_label = $value['label'];

          echo '<dd>' . "\n";
          if ($value['label'] === 'Topic') {
            echo "<a href='/subject/" . $value['content'] . "'>" .  $value['content'] . "</a>";
          } else {
            echo $value['content'];
          }
          echo '</dd>' . "\n";
        }
        echo '</dl>' . "\n";
      }
      ?>

    </div>
  </div>
<?php else: ?>
  <div class="edan-search-result<?php print $class; ?>" id="<?php echo $docs['id']; ?>">
    <div class="edan-row">
      <?php
      $list = app_util_make_list_from_array($docs['content'], 'edanList', false, false);
      print $list;
      ?>
    </div>
  </div>
<?php endif; ?>