<?php<
	include("connexion.php");
?>

<!DOCTYPE html>
<html lang="fr">
  <head>
    <meta charset="utf-8">
    <title>Association créée </title>
  </head>
  <body>
  	<a href="index.php">Index</a><br><br>
	<?php
	if(isset($_POST['projet'])){ 
		$projet = explode(",", $_POST['projet']);

		$insertUtilise = "INSERT INTO utilise VALUES($projet[0], $projet[1],$projet[2])";
		$queryInsertUtilise=pg_query($connexion, $insertUtilise); 

		echo "Association créée";
	

	}

	?>
	</body>
  </html>

