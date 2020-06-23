<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">

</head>
<body>
  
<nav>

<ul>
  <li><a class="active" href="index.php"><b class="lang" key="nav1">Accueil</b></a></li>
  <div class ="dropdown"> 
  <li><a  href="evenements.php"><span class="lang" key="nav2"> Événements </span></a></li>
      <div class="dropdown-content">
          <a class="lang" key="snav3" href="ajouter.php">Ajoutez un evenement</a>  
    </div>
  </div>
  <li>
      <a href="contact.php">Contact</a></li>
  
  <div class="dropdown_lang" style="float:right">
  
    <button class="dropbtn_lang">L
       <i class="fa fa-caret-down"></i>
  </button>
  <div class="dropdown-content_lang">
    <a href="" class="translate" id="fr">Fr</a>
    <a href = ""class="translate" id="en">Eng</a>
  </div>
</div> 
<li style="float:right";><a class = "signup" href="signup.php"><span class="lang" key="nav5">Inscriez-Vous!</span></a></li>
 
  <div id='dropdown'>
	  <ul>
		    <li class='detail' ><a class="lang" key="nav4" href='#'>Connection</a>
		  <ul>
              <label  for="fname">Username:</label>
              <li class="login"><input type="text" placeholder="Username"></input></li>
              <label for="fname">Password</label>
              <li class="password"><input type="password" placeholder="Password"></input></li>
              
              <label>
      <input type="checkbox" checked="checked" name="remember"> Remember me
    </label>
             
              <button type="submit">Login</button>
               
		  </ul>
	   </li>
	</ul>
</div>  
</ul>
</nav>
<script src="./assets/script.js"></script> 
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
</body>
</html>
