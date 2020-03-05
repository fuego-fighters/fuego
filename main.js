function loadDoc() { //src:https://www.w3schools.com/xml/tryit.asp?filename=tryajax_get
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("data").innerHTML = this.responseText;
      }
    };
    xhttp.open("GET", "/ajax", true);
    xhttp.send();
}
function checkAlert() { //src:https://www.w3schools.com/xml/tryit.asp?filename=tryajax_get
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
          if (this.responseText=="fire"){
            alert("Fire In Room1");
          }
      }
    };
    xhttp.open("GET", "/af", true);
    xhttp.send();
}
setInterval(loadDoc, 500);//reloads the html 2hz
setInterval(checkAlert,500);