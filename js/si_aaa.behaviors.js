
  (function ($) {
    if (!Drupal.si_aaa) {
      Drupal.si_aaa = {};
    }
    var win = $(window);
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
    Drupal.si_aaa.splitList = function(list) {
      var num_cols = 2,
      listItem = 'li',
      listClass = 'sub-list';
      list.each(function() {
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
    };

    Drupal.si_aaa.resizeImage = function(context) {
      if ($(window).width() > 500) {
        $('.l-content').find('img').each(function () {
          var img = $(this);
          var imgSrc = img.attr('src');
          if (imgSrc.indexOf('http://ids.si.edu/ids/deliveryService') > -1 ) {
         var imgParams = imgSrc.substr(imgSrc.indexOf('?')+1);
            var parentWidth = $(this).parents('.l-content').width();
            var params = imgParams.split('&');
            var newSrc = 'http://ids.si.edu/ids/deliveryService?' + 'max=' + parentWidth + '&' + params[1];
//            console.log(newSrc);
            $(this).attr('src', newSrc);
          }
        });
      }

    };
    Drupal.si_aaa.slickSlideshow = function(context) {
      if ($(window).width() > 500) {
        $('.l-content').find('img').each(function () {
          var img = $(this);
          var imgSrc = img.attr('src');
          if (imgSrc.indexOf('http://ids.si.edu/ids/deliveryService') > -1 ) {
         var imgParams = imgSrc.substr(imgSrc.indexOf('?')+1);
            var parentWidth = $(this).parents('.l-content').width();
            var params = imgParams.split('&');
            var newSrc = 'http://ids.si.edu/ids/deliveryService?' + 'max=' + parentWidth + '&' + params[1];
//            console.log(newSrc);
            $(this).attr('src', newSrc);
          }
        });
      }

    };
    Drupal.behaviors.si_aaa = {
      attach: function (context, settings) {
				var prev = '<a type="button" data-role="none" class="slick-prev" aria-label="previous"><span class="slick-arrow"></span><span class="sr-only">Previous</span></a>';
				var next = '<a type="button" data-role="none" class="slick-next" aria-label="nex"><span class="slick-arrow"></span><span class="sr-only">Next</span></a>';

        Drupal.si_aaa.splitList($('.split-list ul', context));
        Drupal.si_aaa.resizeImage();
        window.addEventListener('resize', Drupal.si_aaa.resizeImage);
				$('.slick-wrapper').slick({
					dots: true,
					infinite: false,
					speed: 300,
					slidesToShow: 2,
					slidesToScroll: 2,
					//centerMode: true,
					prevArrow: prev,
					nextArrow: next,
					variableWidth: true
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


