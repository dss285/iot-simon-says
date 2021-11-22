// A $( document ).ready() block.
let gameState= document.getElementById ("gameState");
let gameStateSpan= document.getElementById ("gameStateSpan");
let resultText= document.getElementById ("resultText");
let resultTextSpan= document.getElementById ("resultTextSpan");
let startButton = document.querySelector("a#startButton")
let gameRunning = false;
resultText.style.display = "none";
gameState.style.display = "none"
startButton.onclick = async () => {
	await fetch("/newgame")
	if (!gameRunning) {
		gameRunning = true;
		resultText.style.display = "none";
		gameStateSpan.innerHTML = "is running"
		gameState.style.display = "initial";
		var roundsSurvived = parseInt(await (await fetch("/lastgame")).text())-1
		resultTextSpan.innerHTML = roundsSurvived
		gameStateSpan.innerHTML = "is over"
		resultText.style.display = "initial";
		gameRunning = false;
	}

}

$( document ).ready(function() {
    console.log( "ready!" );


    //need to listen incoming signals and call the right functions according to them




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