
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Contact</title>
</head>

<body>
<?php include './assets/navbar.php';?>
<link rel="stylesheet" type="text/css" href="./templates/main.css">
<script src="./assets/script.js"></script> 

<h1>Contact Form</h1>
<div class="box-content_ev">
<form name= "contact_form" action="/action_page.php" onsubmit="return validationContactForm()" method="post" >
<label for="fname">Nom et Prenom</label>
    <input type="text" id="fname" name="fname" placeholder="Nom Prenom">
    <label for="email">Email:</label>
    <input type="text" id="email" name="email" placeholder="Email...">


    <label for="subject">Description</label>
        <textarea id="subject" name="subject" placeholder="Description..." style="height:200px"></textarea>

    <input type="submit" value="Submit">
  </form>


</body>
</html>

