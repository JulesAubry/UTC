<?php 
	include("connexion.php");
	$tri = "titre";
	if(isset($_POST["tri"])){
		$tri = $_POST["tri"];
	}
	if($tri == "date") $tri = "p_date";
	
?>

<!DOCTYPE html>
<html lang="fr">
  <head>
    <meta charset="utf-8">
    <title>Index</title>
  </head>
  <body>

	<a href="projet.php">Ajouter un projet</a><br><br>
	<a href="contact.php">Gérer les contacts</a><br><br>
	<a href="archives.php">Gérer les archives</a><br><br>
	<a href="modele.php">Gérer les modèles</a><br><br>
	<div>
		<div>
			<span>Tri par sélection</span><form method="post"><select name="tri"><option selected>titre</option><option>date</option><option>code</option></select>
												<input type="submit" value="ok"/>
							</form>
		</div>
			
<!-- Tri par modèle @Jules -->
		<div>
			<span>Tri par modèle</span>
			<form method="post">
				<select name="tri_modele">
					<option value="1" <?php if($_POST['tri_modele'] == 1) echo "selected" ?> >Avec modèle(s)</option>
					<option value="0" <?php if($_POST['tri_modele'] == 0) echo "selected" ?>>Sans modèle</option>
				</select>
				<input type="submit" value="ok"/>
			</form>
		</div> </br> </br>
<!-- -->

		<?php
		$query = "SELECT * FROM projet ORDER BY en_avant DESC, $tri";
		$exec = pg_query($connexion, $query);

		if($exec && $_POST['tri_modele'] != '0' && $_POST['tri_modele'] != '1'){

			echo "<table>";
			echo "<legend> Liste des projets</legend>";
			echo "<tr><th>Code</th><th>Titre</th><th>Description</th><th>Date</th><th>Im1</th><th>Im2</th><th>Im3</th><th></th><th></th></tr>";

			while($result = pg_fetch_assoc($exec)){
				$code = $result["code"];
				echo "<tr><td>$code</td>";
				echo "<td>".$result["titre"]."</td>";
				echo "<td>".$result["description"]."</td>";
				echo "<td>".  $result["p_date"] ."</td>";
				if(isset($result['image1']))
					echo "<td><img src='apercu.php?img=image1&code=$code' height='50' width='50'/></td>";
				else echo "<td><img src='images/blanc.jpg' height='50' width='50' /></td> ";
				if(isset($result['image2']))
					echo "<td><img src='apercu.php?img=image2&code=$code' height='50' width='50'/></td>";
				else echo "<td><img src='images/blanc.jpg' height='50' width='50' /></td> ";
				if(isset($result['image3']))
					echo "<td><img src='apercu.php?img=image3&code=$code' height='50' width='50'/></td>";
				else echo "<td><img src='images/blanc.jpg' height='50' width='50' /></td> ";
				echo "<td><form action='modifier_projet.php' method='post'>
						<input type='hidden' name='code' value='$code' />
						<input type='submit' value='détails' />
						</form>
					  </td>";
				echo "<td><form action='supprimer_projet.php' method='post'>
						<input type='hidden' name='code' value='$code' />
						<input type='submit' value='supprimer' />
						</form>
					  </td>";					  
				echo "</tr>";

			}
			echo "</table>";
		}
		else {
			if($_POST['tri_modele'] == 0) {
				$queryTriModele = "SELECT * FROM projet WHERE code NOT IN (SELECT code FROM utilise) ORDER BY code";	
			}
			else {
				$queryTriModele = "SELECT * FROM projet WHERE code IN (SELECT code FROM utilise) ORDER BY code";
			}
			$exec = pg_query($connexion, $queryTriModele);		
			
			if(isset($_POST['tri_modele']) && ($_POST['tri_modele'] == "0" || $_POST['tri_modele'] == "1")){
				echo "<table>";
				echo "<legend>Liste des projets</legend>";
				echo "<tr><th>Code</th><th>Titre</th><th>Description</th><th>Date</th><th>Im1</th><th>Im2</th><th>Im3</th><th></th><th></th></tr>";

				while($result = pg_fetch_assoc($exec)){
					$code = $result["code"];
					echo "<tr><td>$code</td>";
					echo "<td>".$result["titre"]."</td>";
					echo "<td>".$result["description"]."</td>";
					echo "<td>".  $result["p_date"] ."</td>";
					if(isset($result['image1']))
						echo "<td><img src='apercu.php?img=image1&code=$code' height='50' width='50'/></td>";
					else echo "<td><img src='images/blanc.jpg' height='50' width='50' /></td> ";
					if(isset($result['image2']))
						echo "<td><img src='apercu.php?img=image2&code=$code' height='50' width='50'/></td>";
					else echo "<td><img src='images/blanc.jpg' height='50' width='50' /></td> ";
					if(isset($result['image3']))
						echo "<td><img src='apercu.php?img=image3&code=$code' height='50' width='50'/></td>";
					else echo "<td><img src='images/blanc.jpg' height='50' width='50' /></td> ";
					echo "<td><form action='modifier_projet.php' method='post'>
							<input type='hidden' name='code' value='$code' />
							<input type='submit' value='détails' />
							</form>
						  </td>";
					echo "<td><form action='supprimer_projet.php' method='post'>
							<input type='hidden' name='code' value='$code' />
							<input type='submit' value='supprimer' />
							</form>
						  </td>";					  
					echo "</tr>";

				}
				echo "</table>";
			}
		}

?>
	</div>
  </body>
</html>
