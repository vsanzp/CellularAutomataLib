package CellularAutomataLib "Cellular automata modeling and simulation library"

  annotation (
    preferredView = "info",
    Documentation(info="<html>
<p><b>Cellular Automata Models in Modelica</b> </p>
<p>This library can be used to describe 1D, 2D and 3D cellular automata models in Modelica. </p>
<p>It also includes interface models to combine cellular automata with other Modelica models. </p>
<h4>Author:</h4>
<p style=\"margin-left: 30px;\"><a href=\"http://www.euclides.dia.uned.es/vsanz\">Victorino Sanz </a></p>
<p style=\"margin-left: 30px;\">Dpto. Inform&aacute;tica y Autom&aacute;tica, UNED</p>
<p style=\"margin-left: 30px;\">Juan del Rosal, 16</p>
<p style=\"margin-left: 30px;\">28040, Madrid</p>
<p style=\"margin-left: 30px;\">Spain</p>
<p style=\"margin-left: 30px;\">Email: <a href=\"mailto:vsanz@dia.uned.es\">vsanz@dia.uned.es</a></p>
<p style=\"margin-left: 30px;\">Website: <a href=\"http://www.euclides.dia.uned.es/vsanz\">www.euclides.dia.uned.es/vsanz</a></p>
<h4>Copying:</h4>
<p style=\"margin-left: 30px;\"><i>Licensed by Victorino Sanz under the LGPL-3.0 or later. </i></p>
<p style=\"margin-left: 30px;\">Copyright 2024, Victorino Sanz.</p>
<p style=\"margin-left: 30px;\">This program is free software: you can redistribute it and/or modify it under the terms of the GNU Leaser General Public License as published by the Free Software Foundation, either version 3 of the License, or any later version.</p>
<p style=\"margin-left: 30px;\">This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Leaser General Public License for more details.</p>
<p style=\"margin-left: 30px;\">You should have received a copy of the GNU Leaser General Public License along with this program (LICENSE.txt file). If not, see &lt;https://www.gnu.org/licenses/&gt;. Since LGPL is a set of additional permissions on top of the GPL, we also include a copy of the GNU General Public License (at the end of the LICENSE.txt file).</p>
</html>"),
    uses(Modelica(version="4.0.0")),
    Icon(graphics={                                                                                      Rectangle(extent={{-100,50},
              {60,-90}},                                                                                                                            lineColor={28,108,
              200}),                                                                                                                                                          Line(points={{-80,50},
              {-80,-90}},                                                                                                                                                                                            color={28,108,
              200},                                                                                                                                                                                                        smooth = Smooth.None), Line(points={{-60,50},
              {-60,-90}},                                                                                                                                                                                                        color={28,108,
              200},                                                                                                                                                                                                        smooth = Smooth.None), Line(points={{-40,50},
              {-40,-90}},                                                                                                                                                                                                        color={28,108,
              200},                                                                                                                                                                                                        smooth = Smooth.None), Line(points={{-20,50},
              {-20,-90}},                                                                                                                                                                                                        color={28,108,
              200},                                                                                                                                                                                                        smooth = Smooth.None), Line(points={{0,50},{
              0,-90}},                                                                                                                                                                                                        color={28,108,
              200},                                                                                                                                                                                                        smooth = Smooth.None), Line(points={{20,50},
              {20,-90}},                                                                                                                                                                                                        color={28,108,
              200},                                                                                                                                                                                                        smooth = Smooth.None), Line(points={{40,50},
              {40,-90}},                                                                                                                                                                                                        color={28,108,
              200},                                                                                                                                                                                                        smooth = Smooth.None), Line(points = {{0, 80}, {0, -80}}, color={28,108,
              200},                                                                                                                                                                                                        smooth = Smooth.None, origin={-20,50},  rotation = 270), Line(points = {{0, 80}, {0, -80}}, color={28,108,
              200},                                                                                                                                                                                                        smooth = Smooth.None, origin={-20,30},  rotation = 90), Line(points = {{0, 80}, {0, -80}}, color={28,108,
              200},                                                                                                                                                                                                        smooth = Smooth.None, origin={-20,10},  rotation = 90), Line(points = {{0, 80}, {0, -80}}, color={28,108,
              200},                                                                                                                                                                                                        smooth = Smooth.None, origin={-20,-10}, rotation = 90), Line(points = {{0, 80}, {0, -80}}, color={28,108,
              200},                                                                                                                                                                                                        smooth = Smooth.None,                  rotation = 90,
          origin={-20,-30}),                                                                                                                                                                                                        Line(points = {{0, 80}, {0, -80}}, color={28,108,
              200},                                                                                                                                                                                                        smooth = Smooth.None, origin={-20,-50},  rotation = 90), Line(points = {{0, 80}, {0, -80}}, color={28,108,
              200},                                                                                                                                                                                                        smooth = Smooth.None, origin={-20,-70},  rotation = 90),
                                                                                                                                                                                                        Text(extent={{-100,50},
              {60,-90}},                                                                                                                                                                                                        lineColor={0,0,0},
          textString="CA"),
        Line(points={{-100,50},{-80,70},{-60,90}},  color={28,108,200}),
        Line(points={{60,50},{80,70},{100,90}},  color={28,108,200}),
        Line(points={{60,-90},{80,-70},{100,-50}}, color={28,108,200}),
        Line(points={{-60,90},{100,90}},   color={28,108,200}),
        Line(points={{-80,50},{-60,70},{-40,90}},  color={28,108,200}),
        Line(points={{-60,50},{-40,70},{-20,90}},  color={28,108,200}),
        Line(points={{-40,50},{-20,70},{0,90}},  color={28,108,200}),
        Line(points={{-20,50},{0,70},{20,90}},  color={28,108,200}),
        Line(points={{0,50},{20,70},{40,90}},  color={28,108,200}),
        Line(points={{20,50},{40,70},{60,90}},  color={28,108,200}),
        Line(points={{40,50},{60,70},{80,90}},  color={28,108,200}),
        Line(points={{60,30},{80,50},{100,70}}, color={28,108,200}),
        Line(points={{60,10},{80,30},{100,50}}, color={28,108,200}),
        Line(points={{60,-10},{80,10},{100,30}},
                                               color={28,108,200}),
        Line(points={{60,-30},{80,-10},{100,10}},
                                                color={28,108,200}),
        Line(points={{60,-50},{80,-30},{100,-10}},
                                                 color={28,108,200}),
        Line(points={{60,-70},{80,-50},{100,-30}}, color={28,108,200}),
        Line(points={{100,90},{100,-50}},  color={28,108,200}),
        Line(points={{70,60},{70,-80}}, color={28,108,200}),
        Line(points={{90,80},{90,-60}}, color={28,108,200}),
        Line(points={{80,70},{80,-70}}, color={28,108,200}),
        Line(points={{70,60},{-90,60}}, color={28,108,200}),
        Line(points={{80,70},{-80,70}}, color={28,108,200}),
        Line(points={{90,80},{-70,80}}, color={28,108,200})}));
end CellularAutomataLib;
