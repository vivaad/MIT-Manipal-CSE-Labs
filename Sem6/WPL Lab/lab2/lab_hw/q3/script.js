function slide() {
$("#text")
.animate({left: "150px"}, 1000)
.animate({left: "-300px"}, 1000, slide);
}
slide();
