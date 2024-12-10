<?xml version="1.0" encoding="iso-8859-1" ?>
<setup>
<application title="Gasthausreservierung" version="2.0.2.306" author="gak" />
<bde AliasName="GASTHAUS" RESOURCE="0007" DataPath="" dbVersion="2" />
<icons Group="Gasthausreservierung">
<icon title="Gasthausreservierung" target="PROGRAM\gasthaus.exe" main="true" dbUpd="" />
<icon title="Gasthaus DB Verwaltung" target="PROGRAM\gasthausDB.exe" main="" dbUpd="true" />
<icon title="Handbuch" target="PROGRAM\gasthaus.pdf" main="" dbUpd="" />
<icon title="Liesmich" target="PROGRAM\liesmich.txt" main="" dbUpd="" />
<icon title="BDE-Verwaltung" target="BDE\bdeadmin.exe" main="" dbUpd="" />
<icon title="Datenpumpe" target="BDE\datapump.exe" main="" dbUpd="" />
</icons>
<source>
<group name="PROGRAM" destination="">
<file source="..\..\Object\gasthaus.exe" />
<file source="LIESMICH.TXT" />
<file source="..\..\Object\gasthausDB.exe" />
<file source="reports" />
<file source="..\..\Object\srxViewer.DEU" />
<file source="..\..\Object\srxViewer.exe" />
<file source="GASTHAUS.pdf" />
</group>
</source>
</setup>