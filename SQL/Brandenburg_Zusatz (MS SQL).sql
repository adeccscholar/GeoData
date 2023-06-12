Use Geodaten;

EXEC sys.sp_addextendedproperty 
    @name = N'MS_Description', 
    @value = N'Tabelle mit den Daten, die von der Brandenburger Landesbehörde bereit gestellt werden. Die Daten können gemäß der "Datenlizenz Deutschland Namensnennung 2.0" genutzt werden. Quellenvermerk: GeoBasis-DE/LGB, 2019.',
    @level0type = N'SCHEMA', @level0name = N'dbo',
    @level1type = N'TABLE',  @level1name = N'Brandenburg';
	
EXEC sys.sp_addextendedproperty 
    @name = N'MS_Description', 
    @value = N'Im Attribut "Land_ID" ist ein externe Schlüssel mit der Statistik- Kennziffer für das Land "Brandenburg" gespeichert (NUTS 1-Region). Diese Nummern werden zentral vergeben und sollten eindeutig sein.',
    @level0type = N'SCHEMA', @level0name = N'dbo',
    @level1type = N'TABLE',  @level1name = N'Brandenburg',
    @level2type = N'COLUMN', @level2name = N'Land_ID';

EXEC sys.sp_addextendedproperty 
    @name = N'MS_Description', 
    @value = N'Im Attribut "Kreis_ID" ist ein 2 stelliger, externe Schlüssel mit der Statistik- Kennziffer für Kreise und kreisfreien Städte im Land "Brandenburg" gespeichert. Sie entsprechen der NUTS 3 Region und sollte mit der Land_ID zusammen eindeutig sein. ',
    @level0type = N'SCHEMA', @level0name = N'dbo',
    @level1type = N'TABLE',  @level1name = N'Brandenburg',
    @level2type = N'COLUMN', @level2name = N'Kreis_ID';

EXEC sys.sp_addextendedproperty 
    @name = N'MS_Description', 
    @value = N'Mit dieser Sicht werden die Kreise aus der Tabelle "Brandenburg" extrahiert und stehen für Verknüpfungen zur Verfügung.',
    @level0type = N'SCHEMA', @level0name = N'dbo',
    @level1type = N'VIEW',  @level1name = N'vw_Brandenburger_Kreise';
	