$("#update").click(() => {
  $("#card").css({
    "background": $("#bg").val(),
    "font-family": $("#font").val(),
    "font-size": $("#size").val() + "px",
    "border": $("input[name='border']:checked").val()
  });
  $("#greet").text($("#text").val());
  $("#cake").toggle($("#pic").is(":checked"));
});
