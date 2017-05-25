<?php
	include("connexion.php");
?>

<!DOCTYPE html>
<html lang="fr">
  <head>
    <meta charset="utf-8">
    <title>Gestion des images</title>
  </head>
  <body>
  	<a href="index.php">Index</a><br>
  	<?php
		if(isset($_GET['code'])){
			$code = $_GET['code']; 
				$select = "SELECT image1, image2, image3 FROM projet WHERE code = $code";
				$exe = pg_query($connexion, $select);
				if($exe){
					$result = pg_fetch_assoc($exe);
					$stack = array();
					$bool = false; 
					foreach ($result as $key => $var) {
						$stack[$key] = $var;
  						 if(strlen($var) > 2 && !isset($_FILES['im'])){
  						  	echo '<div>';
							echo "<img src='apercu.php?img=$key&code=$code' height='100' width='100'/>";
							echo '<br><br></div>';
						}
						else $bool = $key;
					}

					if(!isset($_FILES['im'])){
						?>
						<span>Ajouter une image</span><br><br>
						<span>Attention, si vous avez déjà mis trois images et que vous comptez en insérer une nouvelle, la dernière sera effacée.</span><br>
						<form method="post" action="image.php?code=<?php echo $code; ?>" enctype="multipart/form-data">
							<label for="im">Fichier JPG :</label><br />
							<input type="file" name="im"/>
							<input type="submit" value="valider" />
						</form>
						<?php
					}
					else{
					$name = $_FILES['im']['name'];
					// On copie l'image et on change les droits pour travailler plus simplement dessus
					// Ce n'était pas spécialement nécessaire j'en conviens
					move_uploaded_file($_FILES['im']['tmp_name'], "images/$name");
					chmod("images/$name", 0777);
					$data = file_get_contents("images/$name");
					$data = pg_escape_bytea($data);
					unlink("images/$name");	
					$insert = "UPDATE projet SET $bool='{$data}' WHERE code=$code";
					$r = pg_query($connexion, $insert);
					if($r)
						echo "Ajout d'image effectué !";
					else echo "Erreur dans l'ajout d'image";

					echo "<a href=''>Recharger la page</a>";
			}
		}
	}
	?>
</body>
  </html>
