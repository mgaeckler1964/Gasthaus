<?xml version="1.0" encoding="iso-8859-1" ?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:template match="/|*">
		<xsl:apply-templates />
	</xsl:template>
	
	<xsl:template match="/gasthaus">
		<html>
			<head>
				<title>Reservierungen</title>
			</head>
			<body>
				<table border="1" cellspacing="0" >
					<tr>
						<th>Datum</th>
						<th>Uhrzeit</th>
						<th>Raum</th>
						<th>Tisch</th>
						<th>Name</th>
						<th>Telefon</th>
						<th>Personen</th>
					</tr>
					<xsl:apply-templates select="reservierung"/>
				</table>
			</body>
		</html>
	</xsl:template>
	
	<xsl:template match="reservierung">
		<tr>
			<td><xsl:value-of select="@datum" /></td>
			<td><xsl:value-of select="@uhrzeit" /></td>
			<td><xsl:value-of select="@raum" /></td>
			<td><xsl:value-of select="@tisch" /></td>
			<td><xsl:value-of select="@name" /></td>
			<td><xsl:value-of select="@telefon" /></td>
			<td><xsl:value-of select="@personen" /></td>
		</tr>
	</xsl:template>
</xsl:stylesheet>