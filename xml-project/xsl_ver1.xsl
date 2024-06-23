<?xml version="1.0"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:fo="http://www.w3.org/1999/XSL/Format">
	<xsl:output method="xml" version="1.0" indent="yes"/>
	<xsl:template match="/">
		<fo:root>
			<fo:layout-master-set>
				<fo:simple-page-master page-height="300mm" page-width="210mm" margin="5mm 25mm 5mm 25mm" master-name="page">
					<fo:region-body margin="20mm 0mm 20mm 0mm"/>
				</fo:simple-page-master>
			</fo:layout-master-set>
			<!--**************************TitlePage***************************-->
			<fo:page-sequence master-reference="page">
				<fo:flow flow-name="xsl-region-body">
					<fo:block-container position="absolute" top="-2.5cm" left="-2.5cm">
						<fo:block position="absolute" text-align="center" font-weight="bold" font-style="italic" margin-left="2cm" font-family="Times New Roman" font-size="30pt" padding-before="50mm" color="blue">
							<fo:block margin-bottom="30mm">
							Каталог на язовирите в България по региони
						</fo:block>
							<fo:external-graphic src="url('resources/titlePage.jpg')" text-align="center" margin-bottom="30mm" content-height="400" content-width="530"/>
						</fo:block>
					</fo:block-container>
				</fo:flow>
			</fo:page-sequence>
			<!--*****************************************************-->
			<!--**************************DescriptionPage***************************-->
			<fo:page-sequence master-reference="page">
				<fo:flow flow-name="xsl-region-body">
					<fo:block-container position="absolute" top="-2.5cm" left="-2.5cm">
						<fo:block position="absolute" font-family="Times New Roman" font-weight="bold" font-style="italic" font-size="20pt" color="black" padding-before="50mm" padding-after="15mm" margin-left="20mm" margin-bottom="20mm">
						Описание на каталога:
						<fo:block position="absolute" text-align="justify" font-family="Times New Roman" font-style="italic" padding-left="5mm" padding-before="15mm" padding-after="15mm" font-size="14pt" margin-left="20mm">
								Библиотечните каталози разкриват всестранно библиотечния фонд пред читателите посредством описание, класифициране и предметизиране на библиотечните материали. В България каталожната система се е развила под влияние на немската библиотечна традиция. Основните видове каталози са:
							</fo:block>
						</fo:block>
					</fo:block-container>
				</fo:flow>
			</fo:page-sequence>
			<!--*****************************************************-->

			<!--**************************DamsPages***************************-->
			<fo:page-sequence master-reference="page">
				<fo:flow flow-name="xsl-region-body">
					<fo:block-container position="relative" top="-2.5cm" left="-2.5cm">
						<fo:block position="relative" text-align="center" font-family="Times New Roman" font-style="italic" font-weight="bold" font-size="20pt" color="blue" padding-before="5mm">
						Язовири в Югозападния регион на България
					</fo:block>
						<fo:block position="relative" padding-before="5mm">
							<xsl:for-each select="//placement[@regionID='SW']/dam">
								<xsl:apply-templates select="."/>
							</xsl:for-each>
						</fo:block>
						<fo:block position="relative" text-align="center" font-family="Times New Roman" font-style="italic" font-weight="bold" font-size="20pt" color="blue" padding-before="5mm">
						Язовири в Северозападния регион на България
					</fo:block>
						<fo:block position="relative" padding-before="5mm">
							<xsl:for-each select="//placement[@regionID='NW']/dam">
								<xsl:apply-templates select="."/>
							</xsl:for-each>
						</fo:block>
						<fo:block position="relative" text-align="center" font-family="Times New Roman" font-style="italic" font-weight="bold" font-size="20pt" color="blue" padding-before="5mm">
						Язовири в Североцентралния регион на България
					</fo:block>
						<fo:block position="relative" padding-before="5mm">
							<xsl:for-each select="//placement[@regionID='NC']/dam">
								<xsl:apply-templates select="."/>
							</xsl:for-each>
						</fo:block>
						<fo:block position="relative" text-align="center" font-family="Times New Roman" font-style="italic" font-weight="bold" font-size="20pt" color="blue" padding-before="5mm">
						Язовири в Североизточния регион на България
					</fo:block>
						<fo:block position="relative" padding-before="5mm">
							<xsl:for-each select="//placement[@regionID='NE']/dam">
								<xsl:apply-templates select="."/>
							</xsl:for-each>
						</fo:block>
						<fo:block position="relative" text-align="center" font-family="Times New Roman" font-style="italic" font-weight="bold" font-size="20pt" color="blue" padding-before="5mm">
						Язовири в Южноизточния регион на България
					</fo:block>
						<fo:block position="relative" padding-before="5mm">
							<xsl:for-each select="//placement[@regionID='SE']/dam">
								<xsl:apply-templates select="."/>
							</xsl:for-each>
						</fo:block>
						<fo:block position="relative" text-align="center" font-family="Times New Roman" font-style="italic" font-weight="bold" font-size="20pt" color="blue" padding-before="5mm">
						Язовири в Южноцентралния регион на България
					</fo:block>
						<fo:block position="relative" padding-before="5mm">
							<xsl:for-each select="//placement[@regionID='SC']/dam">
								<xsl:apply-templates select="."/>
							</xsl:for-each>
						</fo:block>
					</fo:block-container>
				</fo:flow>
			</fo:page-sequence>
			<!--*****************************************************-->
		</fo:root>
	</xsl:template>


	<!--**************************DamTemplate***************************-->

	<xsl:template match="dam">
		<fo:block position="relative" text-align="center" font-family="Times New Roman" font-weight="bold" font-size="18pt" color="black" padding-before="15mm" padding-after="15mm">
			<xsl:value-of select="title/text()"/>
		</fo:block>
		<fo:block position="absolute" text-align="center" padding-before="10mm" padding-after="5mm">
			<xsl:apply-templates select="image"/>
		</fo:block>
		<fo:block position="relative" text-align="justify" font-family="Times New Roman" font-weight="normal" font-size="14pt" color="black" padding-before="5mm" padding-after="15mm">
			<xsl:value-of select="mainInfo/text()"/>
		</fo:block>

		  <fo:inline position="absolute"  text-align="center" font-family="Times New Roman"  font-style="italic" font-weight="normal" font-size="16pt" color="black" padding-before="10mm" padding-after="15mm">
						Язовирна стена:
			</fo:inline>
		<xsl:choose>
			<xsl:when test="damWall">
			<fo:table padding-before="5mm">
		<fo:table-body>
			<fo:table-row>
				<fo:table-cell border="solid" font-family="Times New Roman" font-weight="bold" text-align="center" padding-left="5mm" padding-right="5mm" padding-before="5mm" padding-after="5mm">
					<fo:block>Вид</fo:block>
				</fo:table-cell>
				<fo:table-cell border="solid" font-family="Times New Roman" text-align="center" padding-left="5mm" padding-right="5mm" padding-before="5mm" padding-after="5mm" font-size="14pt">
					<fo:block>
						<xsl:value-of select="./damWall/type/text()"/>
					</fo:block >
				</fo:table-cell>
			</fo:table-row>


			<xsl:if test="./damWall/height">
			<fo:table-row>
				<fo:table-cell border="solid" font-family="Times New Roman" font-weight="bold" text-align="center" padding-left="5mm" padding-right="5mm" padding-before="5mm" padding-after="5mm">
					<fo:block>Височина</fo:block>
				</fo:table-cell>
				<fo:table-cell border="solid" font-family="Times New Roman" text-align="center" padding-left="5mm" padding-right="5mm" padding-before="5mm" padding-after="5mm" font-size="14pt">
					<fo:block   >
						<xsl:value-of select="./damWall/height/text()"/>
					</fo:block >
				</fo:table-cell>
			</fo:table-row>
			</xsl:if>

			<xsl:if test="./damWall/length">
			<fo:table-row>
				<fo:table-cell border="solid" font-family="Times New Roman" font-weight="bold" text-align="center" padding-left="5mm" padding-right="5mm" padding-before="5mm" padding-after="5mm">
					<fo:block>Дължина</fo:block>
				</fo:table-cell>
				<fo:table-cell border="solid" font-family="Times New Roman" text-align="center" padding-left="5mm" padding-right="5mm" padding-before="5mm" padding-after="5mm" font-size="14pt">
					<fo:block   >
						<xsl:value-of select="./damWall/length/text()"/>
					</fo:block >
				</fo:table-cell>
			</fo:table-row>
			</xsl:if>

		</fo:table-body>
	  </fo:table>

			</xsl:when>
		<xsl:otherwise>
		<fo:inline position="absolute" text-align="center" font-family="Times New Roman"  font-weight="normal" font-size="14pt" color="black" padding-before="10mm" padding-after="5mm" >
						/ Няма предоставена информация за язовирна стена ! /
		</fo:inline>

		</xsl:otherwise>
	</xsl:choose>

	<fo:block position="relative" font-family="Times New Roman" font-style="italic" color="black" font-size="16pt"
		padding-before="10mm" padding-after="10mm">
			Основни Характеристики:
			<fo:block position="relative" padding-before="5mm" padding-left="5mm" font-weight="normal" font-size="14pt" >
				<xsl:apply-templates select="traits"/>
			</fo:block>
	</fo:block>

	<fo:block position="relative" font-family="Times New Roman" font-style="italic" color="black" font-size="16pt"
		padding-before="10mm" padding-after="10mm">
			Населено място:
			<fo:inline position="relative" padding-before="5mm" padding-left="5mm" font-weight="normal" font-size="14pt" >
				<xsl:value-of select="populatedPlace/text()"/>
			</fo:inline>
	</fo:block>


	<fo:block position="relative" font-family="Times New Roman" font-style="italic" color="black" font-size="16pt"
		padding-before="10mm" padding-after="10mm">
			Реки притоци:
			<xsl:choose>
			<xsl:when test="count(./riverTributaries/riverTributary) > 1 ">


				<fo:inline position="absolute" text-align="center" font-family="Times New Roman"  font-weight="normal" font-size="14pt" color="black" padding-before="10mm" padding-after="5mm" >
						<xsl:value-of select="./riverTributaries/riverTributary[1]/text()"/>
				</fo:inline>
			  <xsl:for-each select="./riverTributaries/riverTributary[position() >= 2]">
				<fo:inline position="absolute" text-align="center" font-family="Times New Roman"  font-weight="normal" font-size="14pt" color="black" padding-before="10mm" padding-after="5mm" >
						,<xsl:value-of select="text()"/>
				</fo:inline>
			   </xsl:for-each>

			</xsl:when>

			<xsl:when test="count(./riverTributaries/riverTributary) = 1 ">

				<fo:inline position="absolute" text-align="center" font-family="Times New Roman"  font-weight="normal" font-size="14pt" color="black" padding-before="10mm" padding-after="5mm" >
						<xsl:value-of select="./riverTributaries/riverTributary[1]/text()"/>
				</fo:inline>

			</xsl:when>

			<xsl:otherwise>
				<fo:inline position="absolute" text-align="center" font-family="Times New Roman"  font-weight="normal" font-size="14pt" color="black" padding-before="10mm" padding-after="5mm" >
						/ Няма предоставена информация за реки притоци ! /
				</fo:inline>
			</xsl:otherwise>
			</xsl:choose>
	</fo:block>



	<fo:block position="relative" font-family="Times New Roman" font-style="italic" color="black" font-size="16pt"
				padding-before="10mm" padding-after="10mm">
					Интересно място за посещение наблизо:
		<xsl:choose>
			<xsl:when test="nearPlace">
		      			<fo:block position="absolute" text-align="center" padding-before="10mm" padding-after="5mm">
								<xsl:apply-templates select="nearPlace"/>
						</fo:block>
		    </xsl:when>
			<xsl:otherwise>
		      			<fo:inline position="absolute" text-align="center" padding-before="10mm" padding-after="5mm" font-size="14pt">
								/ Няма предоставена информация за интересно място за посещение наблизо ! /
						</fo:inline>
			</xsl:otherwise>
		</xsl:choose>
	</fo:block>






	</xsl:template>

	<!--*****************************************************-->



	<!--**************************************** ImageTemplate ***************************************-->

	<xsl:template match="image">
		<fo:external-graphic src="{unparsed-entity-uri(@href)}" content-height="400" content-width="530"/>
	</xsl:template>

	<!--*****************************************************-->




	<!--**************************************** TraitsTemplate *************************************** -->
	<xsl:template match="traits">
	  <fo:table >
		<fo:table-body>
			<fo:table-row>
				<fo:table-cell border="solid"  font-weight="bold"  font-style="normal" font-family="Times New Roman" text-align="center" padding-left="5mm" padding-right="5mm" padding-before="5mm" padding-after="5mm">
					<fo:block>Дължина</fo:block>
				</fo:table-cell>
				<fo:table-cell border="solid" font-family="Times New Roman"  font-style="normal" text-align="center" padding-left="5mm" padding-right="5mm" padding-before="5mm" padding-after="5mm">
					<fo:block   >
						<xsl:value-of select="length/text()"/>
					</fo:block >
				</fo:table-cell>
			</fo:table-row>
			<fo:table-row>
				<fo:table-cell border="solid" font-weight="bold"  font-style="normal" font-family="Times New Roman" text-align="center" padding-left="5mm" padding-right="5mm" padding-before="5mm" padding-after="5mm">
					<fo:block>Воден обем</fo:block>
				</fo:table-cell>
				<fo:table-cell border="solid" font-family="Times New Roman" font-style="normal" text-align="center" padding-left="5mm" padding-right="5mm" padding-before="5mm" padding-after="5mm" >
					<fo:block   >
						<xsl:value-of select="volume/text()"/>
					</fo:block >
				</fo:table-cell>
			</fo:table-row>
			<fo:table-row>
				<fo:table-cell border="solid" font-weight="bold"  font-style="normal" font-family="Times New Roman" text-align="center" padding-left="5mm" padding-right="5mm" padding-before="5mm" padding-after="5mm">
					<fo:block>Година на създаване</fo:block>
				</fo:table-cell>
				<fo:table-cell border="solid" font-family="Times New Roman" font-style="normal" text-align="center" padding-left="5mm" padding-right="5mm" padding-before="5mm" padding-after="5mm" >
					<fo:block   >
						<xsl:value-of select="year/text()"/>
					</fo:block >
				</fo:table-cell>
			</fo:table-row>



			<xsl:if test="altitude">
			<fo:table-row>
				<fo:table-cell border="solid"  font-weight="bold"  font-style="normal" font-family="Times New Roman" text-align="center" padding-left="5mm" padding-right="5mm" padding-before="5mm" padding-after="5mm">
					<fo:block>Надморска височина</fo:block>
				</fo:table-cell>
				<fo:table-cell border="solid" font-family="Times New Roman" font-style="normal" text-align="center" padding-left="5mm" padding-right="5mm" padding-before="5mm" padding-after="5mm" >
					<fo:block   >
						<xsl:value-of select="altitude/text()"/>
					</fo:block >
				</fo:table-cell>
			</fo:table-row>
			</xsl:if>

			<xsl:if test="width">
			<fo:table-row>
				<fo:table-cell border="solid"  font-weight="bold"  font-style="normal" font-family="Times New Roman" text-align="center" padding-left="5mm" padding-right="5mm" padding-before="5mm" padding-after="5mm">
					<fo:block>Ширина</fo:block>
				</fo:table-cell>
				<fo:table-cell border="solid" font-family="Times New Roman" font-style="normal" text-align="center" padding-left="5mm" padding-right="5mm" padding-before="5mm" padding-after="5mm" >
					<fo:block   >
						<xsl:value-of select="width/text()"/>
					</fo:block >
				</fo:table-cell>
			</fo:table-row>
			</xsl:if>

		</fo:table-body>
	  </fo:table>
	</xsl:template>

	<!--*****************************************************-->


	<!--**************************************** NearPlaceTemplate *************************************** -->
	<xsl:template match="nearPlace">
		<fo:table >
		<fo:table-body>
			<fo:table-row>
				<fo:table-cell border="solid"  font-weight="bold"  font-style="normal" font-family="Times New Roman" text-align="center" padding-left="5mm" padding-right="5mm" padding-before="5mm" padding-after="5mm">
					<fo:block>Име на мястото</fo:block>
				</fo:table-cell>
				<fo:table-cell border="solid" font-family="Times New Roman"  font-style="normal" text-align="center" padding-left="5mm" padding-right="5mm" padding-before="5mm" padding-after="5mm">
					<fo:block   >
						<xsl:value-of select="title/text()"/>
					</fo:block >
				</fo:table-cell>
			</fo:table-row>
			<fo:table-row>
				<fo:table-cell border="solid" font-weight="bold"  font-style="normal" font-family="Times New Roman" text-align="center" padding-left="5mm" padding-right="5mm" padding-before="5mm" padding-after="5mm">
					<fo:block>Дистанция от язовира до мястото</fo:block>
				</fo:table-cell>
				<fo:table-cell border="solid" font-family="Times New Roman" font-style="normal" text-align="center" padding-left="5mm" padding-right="5mm" padding-before="5mm" padding-after="5mm" >
					<fo:block   >
						<xsl:value-of select="distance/text()"/>
					</fo:block >
				</fo:table-cell>
			</fo:table-row>
			<fo:table-row>
				<fo:table-cell border="solid" font-weight="bold"  font-style="normal" font-family="Times New Roman" text-align="center" padding-left="5mm" padding-right="5mm" padding-before="5mm" padding-after="5mm">
					<fo:block>Kратко описание</fo:block>
				</fo:table-cell>
				<fo:table-cell border="solid" font-family="Times New Roman" font-style="normal" text-align="center" padding-left="5mm" padding-right="5mm" padding-before="5mm" padding-after="5mm" >
					<fo:block   >
						<xsl:value-of select="description/text()"/>
					</fo:block >
				</fo:table-cell>
			</fo:table-row>
			<fo:table-row>
				<fo:table-cell border="solid"  font-weight="bold"  font-style="normal" font-family="Times New Roman" text-align="center" padding-left="5mm" padding-right="5mm" padding-before="5mm" padding-after="5mm">
					<fo:block>Изображение</fo:block>
				</fo:table-cell>
				<fo:table-cell border="solid" padding-left="5mm" padding-right="5mm" padding-before="5mm" padding-after="5mm">
						<fo:block position="absolute" text-align="center" padding-left="5mm" padding-right="5mm" padding-before="5mm" padding-after="5mm">
						<fo:external-graphic src="{unparsed-entity-uri(./image/@href)}" content-width="scale-to-fit" content-height="100%" width="100%" scaling="uniform" />
						</fo:block>
				</fo:table-cell>
			</fo:table-row>




		</fo:table-body>
	  </fo:table>

	</xsl:template>

	<!--*****************************************************-->



</xsl:stylesheet>

<xsl:choose>
<xsl:when test =''>

</xsl:when>
<xsl:otherwise>

</xsl:otherwise>
</xsl:choose>