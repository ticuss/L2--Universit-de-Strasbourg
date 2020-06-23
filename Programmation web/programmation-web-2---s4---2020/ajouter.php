<?php

	include('config/db_connect.php');

	$title = $desciption = '';
	$errors = array('desciption' => '', 'title' => '');

	if(isset($_POST['submit'])){
   //check and move file 
    $file =  $_FILES['file']; 
      $fileName = $_FILES['file']['name'];
      $fileTmpName = $_FILES['file']['tmp_name'];
      $fileSize = $_FILES['file']['size'];
      $fileError = $_FILES['file']['error'];
      $fileType = $_FILES['file']['type'];
      
      $fileExt = explode('.',$fileName );
      $fileActualExt = strtolower(end($fileExt));

      $allow = array('jpg','jpeg', 'png' , 'pdf');

      if (in_array($fileActualExt, $allow)) {
        if ($fileError=== 0) {
          if($fileSize < 300000){
              $fileNameNew = uniqid('',true).".".$fileActualExt;
              $fileDestination = 'assets/images/'.$fileNameNew;
           if (!move_uploaded_file($fileTmpName, $fileDestination)){echo "ok"; };
            
            
          }
          else {
            echo " the file is too bigg!!";
          }
        } else {
          echo " error upload";
        }
      } else {
        echo " you can't upload files of this type";
      }


		// check title
		if(empty($_POST['title'])){
			$errors['title'] = 'A title is required';
		} else{
			$title = $_POST['title'];
			if(!preg_match('/^[a-zA-Z\s]+$/', $title)){
				$errors['title'] = 'Title must be letters and spaces only';
			}
    }
    
		// check Description
		if(empty($_POST['desciption'])){
			$errors['desciption'] = 'At least one desciption is required';
		} else{
			$desciption  = $_POST['desciption'];
			
		}

		if(array_filter($errors)){
			//echo 'errors in form';
		} else {
			// escape sql chars
			$desciption = mysqli_real_escape_string($conn, $_POST['desciption']);
			$title = mysqli_real_escape_string($conn, $_POST['title']);
      $fileDestination= mysqli_real_escape_string($conn, $fileDestination);

			// create sql
			$sql = "INSERT INTO Eveniments(title,desciption,img_dest) VALUES('$title','$desciption', '$fileDestination')";

			// save to db and check
			if(mysqli_query($conn, $sql)){
				// success
				header('Location: evenements.php?SUCCESS)))))))))))))))))))))))');
			} else {
				echo 'query error: '. mysqli_error($conn);
			}
			
		}

	} // end POST check

?>

<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="stylesheet" type="text/css" href="./templates/main.css">
<title>Ajouter un evenement</title>
</head>
<body>
<?php include './assets/navbar.php'; ?>
<div class="box-content_ev">
  <form  method="POST" enctype="multipart/form-data">
    <h1>Ajouter un evenement </h1>
    <label for="title">Title de votre evenement</label>
    <input type="text" id="title" name="title" placeholder="Title.." value="<?php echo htmlspecialchars($title) ?>" >
    <div style="color : red" ><?php echo $errors['title']; ?></div>
    <br>
    

    <label for="fdate">Date</label>
    <input type="date" id="date" name="date" required>
    
    <label for="fheure">Heure</label>
    <input type="time" id="appt" name="appt" >
    
       <label for="country"> <br><br>Categorie</label>
    <select id="country" name="country">
      <option value="dance">Dance</option>
      <option value="conversation">Conversation</option>
      <option value="club">Club</option>
    </select>

    <label for="myfile">Selectionne une image:</label>
  <input type="file" id="file" name="file"><br><br>

    <label for="subject">Description</label>
    <textarea id="subject" name="desciption" placeholder="Description..." style="height:200px" value="<?php echo htmlspecialchars($desciption) ?>"></textarea>
    <div style="color : red" ><?php echo $errors['desciption']; ?></div>
    <input type="submit" value="Submit" name="submit">
  </form>

  
</body>

</html>
