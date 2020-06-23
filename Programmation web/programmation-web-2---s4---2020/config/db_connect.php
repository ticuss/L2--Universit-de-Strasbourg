<?php 


$conn = mysqli_connect("localhost","ticus","ticu","database");

if(!$conn){
  echo 'Connection error: '. mysqli_connect_error();
}

$sql = 'SELECT * FROM Eveniments ORDER BY created_at ' ;

$result = mysqli_query($conn,$sql);

$Eveniments = mysqli_fetch_all($result,MYSQLI_ASSOC);
?>