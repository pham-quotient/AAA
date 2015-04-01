(function ($) {

  /**
   * The recommended way for producing HTML markup through JavaScript is to write
   * theming functions. These are similiar to the theming functions that you might
   * know from 'phptemplate' (the default PHP templating engine used by most
   * Drupal themes including Omega). JavaScript theme functions accept arguments
   * and can be overriden by sub-themes.
   *
   * In most cases, there is no good reason to NOT wrap your markup producing
   * JavaScript in a theme function.
   */
 // Drupal.theme.prototype.si_aaa.ExampleButton = function (path, title) {
    // Create an anchor element with jQuery.
 //   return $('<a href="' + path + '" title="' + title + '">' + title + '</a>');
 // };

  /**
   * Behaviors are Drupal's way of applying JavaScript to a page. In short, the
   * advantage of Behaviors over a simple 'document.ready()' lies in how it
   * interacts with content loaded through Ajax. Opposed to the
   * 'document.ready()' event which is only fired once when the page is
   * initially loaded, behaviors get re-executed whenever something is added to
   * the page through Ajax.
   *
   * You can attach as many behaviors as you wish. In fact, instead of overloading
   * a single behavior with multiple, completely unrelated tasks you should create
   * a separate behavior for every separate task.
   *
   * In most cases, there is no good reason to NOT wrap your JavaScript code in a
   * behavior.
   *
   * @param context
   *   The context for which the behavior is being executed. This is either the
   *   full page or a piece of HTML that was just added through Ajax.
   * @param settings
   *   An array of settings (added through drupal_add_js()). Instead of accessing
   *   Drupal.settings directly you should use this because of potential
   *   modifications made by the Ajax callback that also produced 'context'.
   */

  Drupal.behaviors.si_aaa_SplitList = {
    attach: function (context, settings) {
      var num_cols = 2,
      container = $('.split-list ul'),
      listItem = 'li',
      listClass = 'sub-list';
      container.each(function() {
        var items_per_col = new Array(),
        items = $(this).find(listItem),
        min_items_per_col = Math.floor(items.length / num_cols),
        difference = items.length - (min_items_per_col * num_cols);
        for (var i = 0; i < num_cols; i++) {
          items_per_col[i] = i < difference ?  min_items_per_col + 1 : min_items_per_col;
        }
        for (var i = 0; i < num_cols; i++) {
		  var subClass = 'list-' + i;
          $(this).append($('<ul ></ul>').addClass(listClass +' ' + subClass));
          for (var j = 0; j < items_per_col[i]; j++) {
            var pointer = 0;
            for (var k = 0; k < i; k++) {
              pointer += items_per_col[k];
            }
            $(this).find('.' + subClass).last().append(items[j + pointer]);
          }
        }
      });
    }
  }
//  Drupal.behaviors.si_aaa.ExampleBehavior = {
//    attach: function (context, settings) {
      // By using the 'context' variable we make sure that our code only runs on
      // the relevant HTML. Furthermore, by using jQuery.once() we make sure that
      // we don't run the same piece of code for an HTML snippet that we already
      // processed previously. By using .once('foo') all processed elements will
      // get tagged with a 'foo-processed' class, causing all future invocations
      // of this behavior to ignore them.
//      $('.some-selector', context).once('foo', function () {
        // Now, we are invoking the previously declared theme function using two
        // settings as arguments.
//        var $anchor = Drupal.theme('si_aaa.ExampleButton', settings.myExampleLinkPath, settings.myExampleLinkTitle);

        // The anchor is then appended to the current element.
//        $anchor.appendTo(this);
//      });
//    }
//  };

})(jQuery);
