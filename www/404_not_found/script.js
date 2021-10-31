var pageX = window.innerWidth;
var pageY = window.innerHeight;
var mouseY=0;
var mouseX=0;

document.addEventListener('mousemove' , event => {
  //verticalAxis
  mouseY = event.pageY;
  yAxis = (pageY/2-mouseY)/pageY*300;
  //horizontalAxis
  mouseX = event.pageX / -pageX;
  xAxis = -mouseX * 100 - 100;

  $('.box__ghost-eyes').css({ 'transform': 'translate('+ xAxis +'%,-'+ yAxis +'%)' });

  console.log('X: ' + xAxis + 'Y: ' + yAxis);

});
