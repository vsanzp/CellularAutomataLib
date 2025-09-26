within CellularAutomataLib.Examples.CS_2D.C17;
model diffeqmodel "Difference equation SIR model"
  parameter Real r = 0.00006 "infection rate";
  parameter Real a = 0.2 "recovery rate";
  discrete Real S(fixed = true, start = 16000) "susceptible";
  discrete Real I(fixed = true, start = 100) "infected";
  discrete Real R(fixed = true, start = 0) "recovered";
equation
  when sample(0, 1) then
    S = pre(S) - r*pre(S)*pre(I);
    I = pre(I) + r*pre(S)*pre(I) - a*pre(I);
    R = pre(R) + a*pre(I);
  end when;
  annotation (
    experiment(StopTime = 50),
    __Dymola_experimentSetupOutput,
    Documentation(info="<html>
<p>SIR difference equation model</p>
</html>"),
    Icon(graphics={Rectangle(extent={{-80,80},{80,-80}}, lineColor={28,108,200}),
          Text(
          extent={{-80,40},{80,-40}},
          textColor={28,108,200},
          textString="%name")}));
end diffeqmodel;
