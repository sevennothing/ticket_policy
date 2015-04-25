/*
 * test_grade.js
 * Copyright (C) 2015 licj <licj@out.lrserver>
 *
 * Distributed under terms of the MIT license.
 */

var grade = require("./build/Release/ticket_policy");



console.log("ticket policy test start");

var arry = [0.0001, 0.001, 0.01, 0.1, 0.3, 0.5889];

console.log(new Date())


var res = 5;
var i = 0;
while(res !== 0){
	res = grade.ticket_policy(arry);
//	console.log(res);
	i++;
}

/*
var k=0;
while(k !== 2){
	res = grade.ticket_policy(arry);
	i++;
	if(k===1 && res ===0) k=2;
	else if(res === 0) k=1;
}
*/
console.log(new Date())
console.log("Get the ticket is :" +  res + " use " + i);
