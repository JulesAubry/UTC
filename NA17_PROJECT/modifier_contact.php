<?php
	include("connexion.php");
?>

<!DOCTYPE html>
<html lang="fr">
  <head>
    <meta charset="utf-8">
    <title>Modification contact</title>
  </head>
  <body>
  	<a href="index.php">Index</a><br>
  	<?php
		$code = NULL;
		if(isset($_POST) && isset($_POST['code'])){
			$code = $_POST['code'];}
		elseif(isset($_GET) && isset($_GET['c'])){
			$code = $_GET['c'];}
		if((isset($_GET['t']) || (isset($_GET['c']))) && ($code != NULL))
			{
			if($_GET['t'] == 'p'){ // Personne physique
				//$code = $_POST['code'];
				$query1 = "SELECT *  FROM personne_physique WHERE id= '$code' ;";
				$exec1 = pg_query($connexion, $query1);
				if($exec1){
					$result1 = pg_fetch_assoc($exec1);
					echo "<form action='traitement_modifier_contact.php?t=p' method='post'>";
					echo "<label for='nom'>Nom : </label><input type='text' id='nom' name='nom' value='".$result1['nom']."'  maxlength='20' required /><br \><br \>";
					echo "<label for='prenom'>Prénom : </label><input type='text' id='prenom' name='prenom' value='".$result1['prenom']."'  maxlength='20' required /><br \><br \>";
					echo "<label for='employeur'>Employeur : </label>";
					$query2 = "SELECT id, email FROM personne_morale";
					$exec2 = pg_query($connexion, $query2);
					if($exec2){
						echo "<select name='employeur' id='employeur'>";
						while($result2 = pg_fetch_assoc($exec2)){
							
							echo "<option value='".$result2['id']."'";
							if($result2['id'] == $result1['employeur']) // Si c'est son employeur
								echo "selected";
							echo ">".$result2['email']."</option>";

						}
						echo "</select><br \><br \>";
					}
					echo "<input type='hidden' value='".$result1['id']."' id='id' name='id' />";
					echo "<label for='mail'>M@il : </label><input type='email' id='mail' name='mail' value='".$result1['email']."' maxlength='320' /><br \><br \>";
					echo "<label for='titre'>Poste : </label><input type='text' id='poste' name='poste' value='".$result1['poste']."' maxlength='50' /><br \><br \>";
					echo "<input type='submit' value='Modifier' />";
					echo "</form>";
					echo "<br \>Informations concernant le(s) rôle(s) que joue cette personne dans les projet : <br \>";
					$query3 = "SELECT a.code, a.role, p.titre FROM a_pour_role a INNER JOIN projet p ON a.code=p.code WHERE id_contact = '$code';";
					$exec3 = pg_query($connexion, $query3);
					if($exec3){
						while($result3 = pg_fetch_assoc($exec3)){
							echo "* ".$result3['titre'].' ('.$result3['role'].')<br \>';
						}
					}
				}

				
			}
			if($_GET['t'] == 'm'){ // Personne morale
				//$code = $_POST['code'];
				$query2 = "SELECT * FROM personne_morale WHERE id= '$code' ;";
				$exec2 = pg_query($connexion, $query2);
				if($exec2){
					$result2 = pg_fetch_assoc($exec2);
					echo "<form action='traitement_modifier_contact.php?t=m' method='post'>";
					echo "<label for='nom'>Email : </label><input type='email' id='mail' name='mail' value='".$result2['email']."' maxlength='320' /><br \><br \>";
					echo "<label for='nom'>Nom : </label><input type='text' id='nom' name='nom' value='".$result2['nom']."' maxlength='20' required /><br \><br \>";
					echo "<label for='nom'>Type : </label><input type='text' id='type' name='type' value='".$result2['type']."' maxlength='10' /><br \><br \>";
					echo "<input type='hidden' value='".$result2['id']."' id='id' name='id' />";
					echo "<input type='submit' value='Modifier' />";
					echo "</form>";
					echo "<br \>Informations concernant le(s) rôle(s) que joue cette personne dans les projet : <br \>";
					$query3 = "SELECT a.code, a.role, p.titre FROM a_pour_role a INNER JOIN projet p ON a.code=p.code WHERE id_contact = '$code';";
					$exec3 = pg_query($connexion, $query3);
					if($exec3){
						while($result3 = pg_fetch_assoc($exec3)){
							echo "* ".$result3['titre'].' ('.$result3['role'].')<br \>';
						}
					}
				}
			}
		}
	?>
  </body>
  </html>	

