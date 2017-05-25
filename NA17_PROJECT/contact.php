<?php
	include("connexion.php");
?>

<!DOCTYPE html>
<html lang="fr">
	<head>
		<meta charset="utf-8">
		<title>Projet</title>
	</head>
	<body>
		<div>
			<a href='index.php'>Index</a><br \>
			<a href='contact_physique.php'>Ajouter une personne physique</a><br \>
			<a href='contact_morale.php'>Ajouter une personne morale</a><br \><br \>
			<?php // Affichage des personnes déjà existantes
				$query1 = "SELECT p.*, m.nom emp FROM personne_physique p LEFT JOIN personne_morale m ON p.employeur = m.id;";
				$exec1 = pg_query($connexion, $query1);

				if($exec1){
					echo "<table><legend>Liste des contacts (Personnes physiques)</legend>";
					echo "<tr><th>Nom</th><th>Prénom</th><th>Employeur</th><th>Adresse m@il</th><th>Poste</th><th></th><th></th></tr>";

					while($result1 = pg_fetch_assoc($exec1)){
						echo "<tr>";
						echo "<td>".$result1['nom']."</td>";
						echo "<td>".$result1['prenom']."</td>";
						echo "<td>".$result1['emp']."</td>";
						echo "<td>".$result1['email']."</td>";
						echo "<td>".$result1['poste']."</td>";
						echo "<td><form action='modifier_contact.php?t=p' method='post'>
								<input type='hidden' name='code' value='".$result1['id']."' />
								<input type='submit' value='modifier' />
								</form></td>";
						echo "<td><form action='supprimer_contact.php?t=p' method='post'>
								<input type='hidden' name='code' value='".$result1['id']."' />
								<input type='submit' value='Supprimer' />
								</form></td>";
						echo "</tr>";
					}
					echo "</table>";
				}
				echo "<br \><br \>";

				$query2 = "SELECT * FROM personne_morale;";
				$exec2 = pg_query($connexion, $query2);
				if($exec2){
					echo "<table><legend>Liste des contacts (Personnes morales)</legend>";
					echo "<tr><th>Nom</th><th>m@il</th><th>Type</th><th></th><th></th></tr>";
					
					while($result2 = pg_fetch_assoc($exec2)){
						echo "<tr>";
						echo "<td>".$result2['nom']."</td>";
						echo "<td>".$result2['email']."</td>";
						echo "<td>".$result2['type']."</td>";
						echo "<td><form action='modifier_contact.php?t=m' method='post'>
								<input type='hidden' name='code' value='".$result2['id']."' />
								<input type='submit' value='modifier' />
								</form></td>";
						echo "<td><form action='supprimer_contact.php?t=m' method='post'>
								<input type='hidden' name='code' value='".$result2['id']."' />
								<input type='submit' value='Supprimer' />
								</form></td>";
						echo "</tr>";
					}
					echo "</table>";
				}
				
			?>
		</div>
	</body>
</html>
