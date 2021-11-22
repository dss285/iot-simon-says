// A $( document ).ready() block.
var elem = document.querySelector("a#startButton")
elem.onclick = async () => {
	await fetch("/newgame")
}

$( document ).ready(function() {
    console.log( "ready!" );


    //need to listen incoming signals and call the right functions according to them

let gameStateSpan= document.getElementById ("gameStateSpan");
let resultText= document.getElementById ("resultText");
let resultTextSpan= document.getElementById ("resultTextSpan");
let gameLevel = 0 //How to catch gamelevel?



//if game starts:
function gameStarts(){

	resultText.style.visbility =hidden;
	gameStateSpan.innerHTML = "is going on!"
}


//if game is over:
function gameOver(){
	resultTextSpan.innerHTML = gameLevel;
	resultText.style.visbility =visible;
	gameStateSpan.innerHTML = "is over!"
}



});