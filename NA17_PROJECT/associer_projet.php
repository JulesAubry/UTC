<?php
	include("connexion.php");
?>

<!DOCTYPE html>
<html lang="fr">
  <head>
    <meta charset="utf-8">
    <title>Association projet</title>
  </head>
  <body>
  	<a href="index.php">Index</a><br><br>
	<?php

	if(isset($_POST['projet'])){
		$projet = $_POST['projet'];
		$id = $_GET['id'];
		$q = "INSERT INTO associe_a (code1, code2) VALUES ($projet, $id)";
		$r = pg_query($connexion, $q);
		
		if($r == 0)
			echo "Erreur de liaison :(";
		else 
			echo "Liaison effectuée ! ";
		echo "<br><br>";
	}
	
	if(isset($_GET['id'])){ 
		$id = $_GET['id'];
		$query = "SELECT code, titre FROM projet 
				  WHERE code <> $id 
				  AND code NOT IN
				  	(SELECT code2 FROM associe_a WHERE code1 = $id)
				  AND code NOT IN (SELECT code1 FROM associe_a WHERE code2 = $id)
				  ORDER BY titre";
		$res = pg_query($connexion, $query);
		if(pg_num_rows($res) == 0){
			echo "Le projet est deja associé a tous les projets.<br>";
		}
		else{
			echo "Associe le projet à :    ";
			?>
			<form method="post">
				<select name="projet">
				<?php
				while($r = pg_fetch_assoc($res)){
					$num = $r['code'];
					$titre = $r['titre'];
					echo "<option value=$num>$titre</option>";
				}
				?>
				</select>
				<input type="submit" value="ajouter">
			</form>
			<?php
		}

	}
	?>
	</body>
  </html>

