# GeoDaten-Projekt

Das GeoDaten-Projekt ist ein Open-Source-Projekt im Rahmen des "adecc Scholar" Projektes für Lehrzwecke und Analysen erstellt wurde. Es befindet sich im zum Projekt gehörenden GitHub in einem Repository bereitgestellt. Das Projekt zielt darauf ab, Kenntnisse in der modernen C++-Programmierung, der Nutzung von Datenbanken sowie dem Vergleich von C++ mit anderen Programmiersprachen hinsichtlich Effizienz, Ressourcenverbrauch und Entwicklungsaufwand zu vermitteln. Das Projekt verwendet frei zugängliche und rechtlich nutzbare Datenbestände, um verschiedene Ziele und Vergleiche zu ermöglichen.

## Inhalte des Projekts

Das Projekt umfasst die folgenden Aspekte:

- Programmieren mit modernem C++: Verwendung von Ranges, Concepts, compile-time Ausdrücken und Metaprogrammierung.
- Nutzung von Datenbanken: Implementierung einer neuen Bibliothek für den Zugriff auf Datenbanken mit Qt und zukünftig auch mit FireDac.
- Vergleich zwischen verschiedenen Datenbanktypen: Vergleich von relationalen Datenbanken und NoSQL-Datenbanken hinsichtlich ihrer Leistung und Ressourcennutzung.
- Vermittlung von Datenbank-Know-how: Diskussion über Themen wie Normalisierung, Architektur und Datenanalyse in Bezug auf relationale Datenbanken.
- Testen verschiedener Ansätze: Verwendung reichhaltiger Testdaten, um verschiedene Ansätze zu testen und neue Erkenntnisse zu gewinnen.
- Vergleich von SQL- und NoSQL-Datenbanken: Analyse von Vor- und Nachteilen sowie Auswirkungen auf den Energieverbrauch.

# Lizenzierung

Die Quelltexte des Projekts stehen unter der GNU General Public License (GPL). Die verwendete Bibliothek "adecc Scholar" verwendet die MIT-Lizenz.

## Hinweis zur "ConvertETRS89ToWGS84"-Funktion
Die Implementierung der Methode "ConvertETRS89ToWGS84" in der Klasse "MyLocation" basiert auf Beispielen und Posts aus Stackoverflow bzw. Stackexchange. Die Funktion verwendet den Algorithmus der Java-Methode "UTM2Deg", die unter der CC BY-SA-Lizenz steht. Gemäß den Bedingungen dieser Lizenz wird auch die C++-Implementierung unter der CC BY-SA-Lizenz veröffentlicht. Der Urheberrechtsvermerk für die C++-Methode "ConvertETRS89ToWGS84" bleibt bestehen.

Quelle: Stackoverflow - Convert Lat/Lon to UTM
© 2023 Stack Exchange Inc; Benutzerbeiträge lizenziert unter CC BY-SA, Benutzer: user2548538

## Datenquellen und Lizenzen
Die im Projekt verwendeten Daten stammen aus verschiedenen Quellen und werden wie folgt lizenziert:

Brandenburg: Die Daten können gemäß der "Datenlizenz Deutschland Namensnennung 2.0" genutzt werden. Quellenvermerk: GeoBasis-DE/LGB, 2019.

Berlin: Die Nutzung der Daten erfolgt gemäß der "Datenlizenz Deutschland - Namensnennung - Version 2.0". Der Quellenvermerk lautet "Geoportal Berlin / Adressen Berlin". Es sind die datenschutzrechtlichen Bestimmungen, insbesondere das Bundesdatenschutzgesetz, zu beachten. Die Lizenz kann über https://www.govdata.de/dl-de/by-2-0 abgerufen werden.

Thüringen: Für die Nutzung digitaler Geobasisdaten und frei zugänglicher Geodatendienste des TLVermGeo gelten die Nutzungsbedingungen nach der "Datenlizenz Deutschland - Namensnennung, Version 2.0" unter Verwendung des Quellenvermerks "© GDI-Th".

Sachsen: Die Daten stehen unter der "Open Data Datenlizenz Deutschland - Namensnennung - Version 2.0" und sind Eigentum von Geobasisinformation und Vermessung Sachsen (GeoSN). Der Quellenvermerk lautet "Geodaten Sachsen".

Darüber hinaus sind im Projekt Daten enthalten, die von anderen Benutzern bereitgestellt wurden. Diese Daten wurden in die Datenbank integriert und sollten die Aktualität und Korrektheit der Informationen berücksichtigen. Eine spezifische Lizenzangabe für diese Benutzerdaten liegt nicht vor.

## zusätzliche Quellen und verwendete Informationen

Die Wikipedia wurde als Informationsquelle genutzt, um Kenntnisse über Geo-Datenstrukturen zu erlangen und Grundlagen für Aufgaben für ChatGPT zu erstellen oder Verknüpfungen und Berechnungen in den oben erwähnten Daten durchzuführen. Es wurden jedoch keine direkten Informationen aus der Wikipedia übernommen. Zur Aufbereitung der Daten und Ergänzung einer Informationen wurde die KI "ChatGPT" verwendet.

# Haftungsausschluss
Die im GeoDaten-Projekt bereitgestellten Informationen und Daten werden nach bestem Wissen und Gewissen zur Verfügung gestellt. Es wird jedoch keine Gewähr für die Richtigkeit, Vollständigkeit oder Aktualität der Daten übernommen. Diese ist für die Ziele dieses Projektes aber auch nicht wichtig. Die Nutzung der Daten erfolgt auf eigenes Risiko. Bei einer von diesem Projekt abweichende Nutzung, sollte die Qualität der Daten geprüft werden. 

Es liegt in der Verantwortung der Benutzer, die rechtlichen Bestimmungen und Lizenzen der verwendeten Datenquellen zu überprüfen und einzuhalten.

Bei Fragen zu den Datenquellen, Lizenzen oder anderen Aspekten des Projekts wenden Sie sich bitte an die Projektverantwortlichen.
