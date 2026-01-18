function bounce() {
$("#ball")
.animate({bottom: "200px"}, 600)
.animate({bottom: "0px"}, 600, bounce);
}
bounce();
