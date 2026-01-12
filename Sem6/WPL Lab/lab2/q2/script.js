$(document).ready(function(){
	function calculate(op) {
		let n1 = parseFloat($("#num1").val());
		let n2 = parseFloat($("#num2").val());
		let res = "";

		if(isNaN(n1) || isNaN(n2)) {
			res = "Please enter valid numbers!";
		} else {
			switch(op) {
				case "add": res = n1 + n2; break;
				case "subtract": res = n1 - n2; break;
				case "multiply": res = n1 * n2; break;
				case "divide":
					res = (n2 !== 0) ? (n1 / n2) : "Cannot divide by zero!";
					break;
			}
		}
		$("#result").text("Result: " + res);
	}

	// Button click events
	$("#add").click(function(){ calculate("add"); });
	$("#subtract").click(function(){ calculate("subtract"); });
	$("#multiply").click(function(){ calculate("multiply"); });
	$("#divide").click(function(){ calculate("divide"); });
});