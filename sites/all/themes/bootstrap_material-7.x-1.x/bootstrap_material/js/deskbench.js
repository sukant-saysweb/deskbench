/*
(function($){
  $(".button-collapse").sideNav();
  $('.button-collapse').click(function(){alert('kjsdf');});
  $('#tst').click(function(){alert('kjsdf');});
}(jQuery));
*/
/*
(function($){
  Drupal.behaviors.theme = {
    attach: function (context, settings) {
      $('.button-collapse').click(function(){
        alert('sdjk');
      });
    }
  }
})(jQuery);
*/
/*
$(document).ready(function () {
  alert('hb');
  // Do some fancy stuff.
});
*/
(function($){
  $('.collapsible').collapsible();
  $(".button-collapse").sideNav();
})(jQuery);

$(document).ready(function(){
    $('.collapsible').collapsible();
  });