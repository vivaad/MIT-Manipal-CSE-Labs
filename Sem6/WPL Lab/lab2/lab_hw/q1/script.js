$("#bill").click(() => {
let q = parseInt($("#qty").val());
let total = 0;

$(".product:checked").each(function () {
if ($(this).val() == "Mobile") total += 10000;
if ($(this).val() == "Laptop") total += 40000;
});

if (total == 0 || isNaN(q)) {
alert("Invalid input");
return;
}

alert("Total Amount: " + total * q);
});
