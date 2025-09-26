within CellularAutomataLib.Examples.CS_2D.C17;
model eqmodel "Differential equation SIR model"
  parameter Real r = 0.00006 "infection rate";
  parameter Real a = 0.2 "recovery rate";
  Real S(fixed = true, start = 16000) "susceptible";
  Real I(fixed = true, start = 100) "infected";
  Real R(fixed = true, start = 0) "recovered";
equation
  der(S) = -r*S*I;
  der(I) = r*S*I - a*I;
  der(R) = a*I;
  annotation (
    experiment(StopTime = 50),
    __Dymola_experimentSetupOutput,
    Documentation(info="<html>
<p>SIR differential equation model</p>
</html>"),
    Icon(graphics={Rectangle(extent={{-80,80},{80,-80}}, lineColor={28,108,200}),
          Text(
          extent={{-80,40},{80,-40}},
          textColor={28,108,200},
          textString="%name")}));
end eqmodel;
