
 <?php
include('config/db_connect.php');

$sql = 'SELECT * FROM Eveniments ORDER BY created_at ';
$result = mysqli_query($conn,$sql);

$Eveniments = mysqli_fetch_all($result,MYSQLI_ASSOC);

?>


<!DOCTYPE html>
<html>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<meta name="author" content="Bogdanas Constantin">
<meta name="description" content="TP2">
<head>
<title>Evenements</title>
<head>


<body>
<?php include './assets/navbar.php'; ?>
<link rel="stylesheet" type="text/css" href="./templates/main.css">
<h1>Evenements</h1>
 
        
        
</div>
<?php foreach($Eveniments as $even){ ?> 
<div class="box-content_ev">
        
<h2 class="article"><?php echo htmlspecialchars($even['title']); ?> </h2>

            <img class="img-article" src="./<?php echo htmlspecialchars($even['img_dest'])?>">
            </br>
                <p class="text-article" name = "desciption">
                <?php echo htmlspecialchars($even['desciption']); ?>
                </p>
                
            </div>
        </div><?php } ?> 
    </div>
    </div>
    </div>
    <script src="./assets/script.js"></script> 
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
</div>
<?php include './assets/footer.php';?>
</body>

</html>
