/*
 * test_grade.js
 * Copyright (C) 2015 licj <licj@out.lrserver>
 *
 * Distributed under terms of the MIT license.
 */

var grade = require("./build/Release/ticket_policy");



console.log("ticket policy test start");

var arry = [0.0001, 0.001, 0.01, 0.1, 0.8889];

console.log(new Date())
var res = 5;
var i = 0;
while(res>0){
	res = grade.ticket_policy(arry);
	i++;
}

console.log(new Date())
console.log("Get the ticket is :" +  res + " use " + i);
