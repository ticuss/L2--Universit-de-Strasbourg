<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<meta name="author" content="Bogdanas Constantin">
<meta name="description" content="TP2">
<title>Inscriez-vous</title>
<?php include './assets/navbar.php'; ?> 
</head>
<!DOCTYPE html>
<html>

<body>

<form action="/action_page.php" >
  <div class="box-content_ev">
    <h1>Inscriez-vous</h1>
    <p><b>Entrez votre donnees.</b></p>
    <br>

    <label for="email"><b>Email</b></label>
    <input type="text" placeholder="Enter Email" name="email" required>

    <label for="psw"><b>Password</b></label>
    <input type="password" placeholder="Enter Password" name="psw" required>

    <label for="psw-repeat"><b>Repeat Password</b></label>
    <input type="password" placeholder="Repeat Password" name="psw-repeat" required>
    
    <label>
      <input type="checkbox" checked="checked" name="remember" style="margin-bottom:15px"> Remember me
    </label>
    <div class="clearfix">
      <button type="button" class="cancelbtn">Annuler</button>
      <button type="submit" class="signupbtn">Sign Up</button>
    </div>
  </div>
</form>
<script src="./assets/script.js"></script> 
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
<?php include './assets/main.php'; ?>
<?php include './assets/footer.php'; ?>
</body>
</html>