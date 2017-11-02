"use strict";
// Client-side interactions with the browser.

// Make connection to server when web page is fully loaded.
var socket = io.connect();
$(document).ready(function() {

	$('#modeRock0').click(function(){
		sendCommand("modeRock0");
	});
	$('#modeRock1').click(function(){
		sendCommand("modeRock1");
	});
	$('#modeRock2').click(function(){
		sendCommand("modeRock2");
	});
	$('#volumeDown').click(function(){
		sendCommand("volumeDown");
	});
	$('#volumeUp').click(function(){
		sendCommand("volumeUp");
	});
	$('#tempoDown').click(function(){
		sendCommand("tempoDown");
	});
	$('#tempoUp').click(function(){
		sendCommand("tempoUp");
	});
	
	socket.on('commandReply', function(result) {
		$('#volumeid').val(result);
	});
	
});

function sendCommand(message) {
	socket.emit('beatbox', message);
};
