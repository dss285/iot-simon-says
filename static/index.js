// A $( document ).ready() block.
let gameState= document.getElementById ("gameState");
let gameStateSpan= document.getElementById ("gameStateSpan");
let resultText= document.getElementById ("resultText");
let resultTextSpan= document.getElementById ("resultTextSpan");
let startButton = document.querySelector("a#startButton")
let scorePlayers = {"Glynis" : document.querySelector("#glynisScore"), "Tommi" : document.querySelector("#tommiScore"), "Teija" : document.querySelector("#teijaScore")}
let gameRunning = false;
let players = new Map();
resultText.style.display = "none";
gameState.style.display = "none"
startButton.onclick = async () => {
	await fetch("/newgame")
	if (!gameRunning) {
		var player = document.querySelector('input[name="player"]:checked').value
		if(!players.get(player)) {
			players.set(player, 0)
		}
		gameRunning = true;
		resultText.style.display = "none";
		gameStateSpan.innerHTML = "is running"
		gameState.style.display = "initial";
		var roundsSurvived = parseInt(await (await fetch("/lastgame")).text())-1
		resultTextSpan.innerHTML = roundsSurvived
		gameStateSpan.innerHTML = "is over"
		resultText.style.display = "initial";
		gameRunning = false;
		if(players.get(player) < roundsSurvived) {
			players.set(player, roundsSurvived)
			scorePlayers[player].innerHTML = roundsSurvived
		}
		console.log(players)
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